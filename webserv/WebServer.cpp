/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:36:44 by estosche          #+#    #+#             */
/*   Updated: 2025/03/11 14:05:04 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "ErrorHandler.hpp"
#include "MultipartParser.hpp"

void WebServer::sendAccumulatedResponses(int clientFd) {
	for (std::vector<std::string>::iterator it = accumulatedResponses.begin(); it != accumulatedResponses.end(); ++it) {
		ssize_t bytesSent = send(clientFd, it->c_str(), it->size(), 0);
		if (bytesSent == -1) {
			std::cerr << "Error sending response to client" << std::endl;
			close(clientFd);
			break;
		} else if (bytesSent == 0) {
			std::cerr << "Client disconnected during response send." << std::endl;
			close(clientFd);
			break;
		}
	}
}

void WebServer::handleCgiRequest(const char* path, const char* cgiExecutable, const char* method, const char* queryString, const char* body) {
    std::string fullPath = std::string(path);
    CgiHandler cgiHandler(cgiExecutable, fullPath.c_str());

    std::string cgiOutput;
    int cgiStatusCode = 0;
	
    try {
        if (strcmp(method, "GET") == 0) {
			std::cout << "📥 Requête reçue: GET CGI " << path << std::endl;
            cgiOutput = cgiHandler.executeCgi(method, queryString, "");
			cgiStatusCode = 200;
        } else if (strcmp(method, "POST") == 0) {
			std::cout << "📥 Requête reçue: POST CGI " << path << std::endl;
            cgiOutput = cgiHandler.executeCgi(method, "", body);
			cgiStatusCode = 200;
        }
    } catch (const std::exception& e) {
        cgiOutput = "Erreur interne du serveur: " + std::string(e.what());
        cgiStatusCode = 500;
		HttpResponse response = errorHandler.generateErrorResponse(500);
        accumulatedResponses.push_back(response.toString());
        return;
    }

    HttpResponse response;
    response.setStatusCode(cgiStatusCode);
    response.setBody(cgiOutput);
    response.setHeader("Content-Type", "text/html");

    char contentLength[20];
    snprintf(contentLength, sizeof(contentLength), "%zu", cgiOutput.size());
    response.setHeader("Content-Length", contentLength);
    accumulatedResponses.push_back(response.toString());
}

std::string WebServer::getMimeType(const std::string& path) {
	size_t dotPos = path.rfind('.');
	if (dotPos == std::string::npos) {
		return "application/octet-stream";
	}
	std::string extension = path.substr(dotPos + 1);
	if (extension == "html") return "text/html";
	if (extension == "css") return "text/css";
	if (extension == "js") return "application/javascript";
	if (extension == "png") return "image/png";
	if (extension == "jpg" || extension == "jpeg") return "image/jpeg";
	if (extension == "gif") return "image/gif";
	if (extension == "mp3") return "audio/mpeg";
	if (extension == "svg") return "image/svg+xml";
	if (extension == "ico") return "image/x-icon";
	if (extension == "txt") return "text/plain";
	return "application/octet-stream";
}

WebServer::WebServer(const Config& config)
	: config(config),
	  errorHandler(config),
	  root(config.getRoot()), 
	  epoll_fd(-1),
	  running(true), 
	  admin(config.getAdmin()){
		
		ports = config.getPorts();
		if (ports.size() == 0) {
			std::cerr << "Error: No ports defined in config." << std::endl;
			exit(EXIT_FAILURE);
		}
		std::vector<ServerConfig> servers = config.getServers();
	for (size_t i = 0; i < servers.size(); ++i) {
		ServerConfig& server = servers[i];

		if (server.client_max_body_size > 0) {
			this->client_max_body_size = server.client_max_body_size;
		} else {
			this->client_max_body_size = 50 * 1024 * 1024;
		}

		for (size_t j = 0; j < server.locations.size(); ++j) {
			LocationConfig& location = server.locations[j];

			if (location.client_max_body_size > 0) {
				this->client_max_body_size = location.client_max_body_size;
			}
			if (!location.index.empty()) {
				locationIndexes[location.path] = location.index;
			}
		}
	} 
}

std::string WebServer::getApiIndexFromLocation(const std::string &path) {
	std::map<std::string, std::string>::iterator it = locationIndexes.find(path);
	
	if (it != locationIndexes.end()) {
		return it->second;
	} else {
		return "";
	}
}

WebServer::~WebServer(){
	stop();
}


int WebServer::create_and_add_server_socket(int port) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Error creating server socket" << std::endl;
        return -1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "Error setting socket option SO_REUSEADDR" << std::endl;
        close(server_fd);
        return -1;
    }

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error binding socket to port " << port << std::endl;
        close(server_fd);
        return -1;
    }

    if (listen(server_fd, 10) < 0) {
        std::cerr << "Error listening on socket" << std::endl;
        close(server_fd);
        return -1;
    }

    if (epoll_fd == -1) {
        epoll_fd = epoll_create1(0);
        if (epoll_fd == -1) {
            std::cerr << "Error creating epoll" << std::endl;
            close(server_fd);
            return -1;
        }
    }

    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) == -1) {
        std::cerr << "Error adding server socket to epoll" << std::endl;
        close(server_fd);
        return -1;
    }

    return server_fd;
}


void WebServer::start() {
	std::vector<int> server_fds;
	for (size_t i = 0; i < ports.size(); ++i) {
		int port = ports[i];
		int server_fd = create_and_add_server_socket(port);
		if (server_fd == -1) {
			std::cerr << "Erreur avec le serveur sur le port " << port << ", il n'a pas pu être lancé." << std::endl;
			continue;
		}
		server_fds.push_back(server_fd);
		std::cout << "✅ Serveur en écoute sur le port " << port << std::endl;
	}

	struct epoll_event events[50];
	bool isMainClientConnected = false;

	while (running) {
		int num_events = epoll_wait(epoll_fd, events, 50, -1);
		if (num_events == -1) {
			break ;
		}

		for (int i = 0; i < num_events; i++) {
			event_fd = events[i].data.fd;
			bool isServerFd = false;
			int listeningPort = -1;

			for (size_t j = 0; j < server_fds.size(); ++j) {
				if (server_fds[j] == event_fd) {
					isServerFd = true;
					listeningPort = ports[j];
					break;
				}
			}

			if (isServerFd) {
				struct sockaddr_in address;
				socklen_t addr_len = sizeof(address);
				int client_fd = accept(event_fd, (struct sockaddr*)&address, &addr_len);
				if (client_fd < 0) {
					std::cerr << "Error accepting client connection" << std::endl;
					continue;
				}

				client_ports[client_fd] = listeningPort;

				if (!isMainClientConnected) {
					std::cout << "📌 Nouveau client connecté sur le port " << listeningPort << std::endl;
					isMainClientConnected = true;
				}

				struct epoll_event client_event;
				client_event.events = EPOLLIN | EPOLLRDHUP;
				client_event.data.fd = client_fd;
				if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &client_event) == -1) {
					std::cerr << "Error adding client socket to epoll" << std::endl;
					close(client_fd);
					continue;
				}
			} else {
				if (events[i].events & EPOLLRDHUP) {
					close(event_fd);
					epoll_ctl(epoll_fd, EPOLL_CTL_DEL, event_fd, NULL);
					client_ports.erase(event_fd);
					isMainClientConnected = false;
				} else if (events[i].events & EPOLLIN){
					handleClient(event_fd);
				}
				else if  (events[i].events & EPOLLOUT) {
					sendAccumulatedResponses(event_fd);
				}
			}
		}
	}

	stop();
}

void WebServer::handleClient(int clientSocket) {
	const int bufferSize = 4096;
	char buffer[bufferSize];
	std::string request;
	int bytesRead;

	while ((bytesRead = recv(clientSocket, buffer, bufferSize, 0)) > 0) {
		request.append(buffer, bytesRead);

		int contentLength = atoi(getHeader(request, "Content-Length").c_str());
		int headersSize = getHeadersSize(request);
		if (static_cast<int>(request.size()) >= contentLength + headersSize) {
			break;
		}
	}
	if (bytesRead == -1) {
		std::cerr << "Error receiving data from client" << std::endl;
		close(clientSocket);
		return;
	} else if (bytesRead == 0) {
		close(clientSocket);
		return;
	}
	int clientPort = client_ports[clientSocket];
	handleRequest(clientSocket, request, clientPort);
	if (request.find("Content-Type: application/octet-stream") != std::string::npos) {
		while ((bytesRead = recv(clientSocket, buffer, bufferSize, 0)) > 0) {
			if (!writeFileChunk(buffer, bytesRead)) {
				close(clientSocket);
				return;
			}
			if (bytesRead < bufferSize) {
				break;
			}
		}
	}

	sendAccumulatedResponses(clientSocket);
	accumulatedResponses.clear();
	request.clear();
	
	struct epoll_event event;
	event.events = EPOLLIN | EPOLLOUT | EPOLLRDHUP;
	event.data.fd = clientSocket;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_MOD, clientSocket, &event) == -1) {
		std::cerr << "Error modifying client socket to epoll" << std::endl;
		close(clientSocket);
	}
}

int WebServer::writeFileChunk(const char* buffer, int bytesRead) {
	std::ofstream outFile("received_file", std::ios::app | std::ios::binary);
	if (outFile.is_open()) {
		outFile.write(buffer, bytesRead);
		if (!outFile) {
			std::cerr << "❌ Erreur lors de l'écriture dans le fichier." << std::endl;
			outFile.close();
			return 0;
		}
		outFile.close();
	} else {
		std::cerr << "❌ Impossible d'ouvrir le fichier pour écriture." << std::endl;
		return 0;
	}
	return 1;
}

void WebServer::handleRequest(int clientFd, const std::string &request, int clientPort) {
    HttpRequest httpRequest;

    if (!httpRequest.parse(request)) {
		HttpResponse response = errorHandler.generateErrorResponse(400);
        accumulatedResponses.push_back(response.toString());
        return;
    }

    std::string methodStr = httpRequest.getMethod();
    std::string pathStr = httpRequest.getPath();
    std::string bodyStr = httpRequest.getBody();
    std::string queryString = httpRequest.getQueryString();
    const char* method = methodStr.c_str();
    const char* path = pathStr.c_str();
    const char* body = bodyStr.c_str();
    const char* query = queryString.c_str();

	std::set<std::string> allowedMethods = config.getAllowedMethods(pathStr);
	
	if (!allowedMethods.empty() && allowedMethods.find(methodStr) == allowedMethods.end()) {
		std::cout << "Méthode non supportée : " << methodStr << std::endl;
		HttpResponse response = errorHandler.generateErrorResponse(405);
		accumulatedResponses.push_back(response.toString());
		return;
	}
	
	

	const char* extension = strrchr(path, '.');
	if (extension != NULL && strcmp(extension, ".php") == 0) {
		const char* cgiExecutable = "/usr/bin/php";
		std::string fullPath = config.getRoot() + path;
		if (strcmp(method, "GET") == 0 || strcmp(method, "POST") == 0) {
			handleCgiRequest(fullPath.c_str(), cgiExecutable, method, query, body);
			return;
		} else {
			HttpResponse response = errorHandler.generateErrorResponse(404);
			accumulatedResponses.push_back(response.toString());
			return;
		}
	}

    if (strncmp(path, "/cgi-bin/", 9) == 0) {
        std::string cgiPath = path; 

        std::string cgiExecutable = config.getCgiPass("/cgi-bin/");

        std::string cgiIndex = config.getIndex("/cgi-bin/");

        std::string fullCgiPath;
        if (!cgiPath.empty()) {
            fullCgiPath = config.getRoot() + cgiPath + cgiIndex;
        } else {
            fullCgiPath = config.getRoot() + "/" + cgiIndex;
        }

        if (strcmp(method, "GET") == 0 || strcmp(method, "POST") == 0) {
            handleCgiRequest(fullCgiPath.c_str(), cgiExecutable.c_str(), method, query, body);
            return;
        } else {
            HttpResponse response = errorHandler.generateErrorResponse(404);
            accumulatedResponses.push_back(response.toString());
            return;
        }
    }

    if (strcmp(method, "GET") == 0) {
        handleGet(path, clientPort);
    } else if (strcmp(method, "POST") == 0) {
        handlePost(clientFd, httpRequest, clientPort);
    } else if (strcmp(method, "DELETE") == 0) {
        handleDelete(path);
    } else {
        HttpResponse response = errorHandler.generateErrorResponse(404);
        accumulatedResponses.push_back(response.toString());
    }
}

std::string generateDirectoryListing(const std::string &path) {
    std::stringstream body;
    DIR *dir = opendir(path.c_str());
    if (dir == NULL) {
        std::cerr << "Erreur lors de l'ouverture du répertoire: " << path << std::endl;
        return "";
    }

    struct dirent *entry;
    body << "<html><body><h1>Liste des fichiers dans " << path << "</h1><ul>";

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') { 
            body << "<li><a href='" << path << (path.empty() || path[path.size() - 1] == '/' ? "" : "/") << entry->d_name << "'>" << entry->d_name << "</a></li>";
        }
    }

    closedir(dir);
    body << "</ul></body></html>";
    return body.str();
}

void WebServer::handleGet(const std::string &path, int port) {
	
    const ServerConfig* selectedServer = NULL;
    std::vector<ServerConfig> servers = config.getServers();
    
    for (size_t i = 0; i < servers.size(); ++i) {
        if (std::find(servers[i].ports.begin(), servers[i].ports.end(), port) != servers[i].ports.end()) {
            selectedServer = &servers[i];
            break;
        }
    }

    if (!selectedServer) {
		HttpResponse response = errorHandler.generateErrorResponse(500);
        accumulatedResponses.push_back(response.toString());
        return;
    }

    const LocationConfig* location = NULL;
    if (path == "/") {
        for (size_t j = 0; j < selectedServer->locations.size(); ++j) {
            if (selectedServer->locations[j].path == "/") {
                location = &selectedServer->locations[j];
                break;
            }
        }
    }

    if (!location) {
        for (size_t j = 0; j < selectedServer->locations.size(); ++j) {
            if (path.find(selectedServer->locations[j].path) == 0) {
                location = &selectedServer->locations[j];
                break;
            }
        }
    }
	if (path == "/download/lyrics") {
		std::cout << "📥 Requête reçue: GET" << " " << path << std::endl;
		std::string filePath = "www/static/lyrics.pdf";


		struct stat fileStat;
		if (stat(filePath.c_str(), &fileStat) != 0) {
			HttpResponse response = errorHandler.generateErrorResponse(404);
			accumulatedResponses.push_back(response.toString());
			return;
		}

		if (access(filePath.c_str(), R_OK) != 0) {
			HttpResponse response = errorHandler.generateErrorResponse(403);
			accumulatedResponses.push_back(response.toString());
			return;
		}

		std::ifstream file(filePath.c_str(), std::ios::binary);
		if (!file) {
			HttpResponse response = errorHandler.generateErrorResponse(500);
			accumulatedResponses.push_back(response.toString());
			return;
		}
	
		std::string body;
		char buffer[1024];
		while (file.read(buffer, sizeof(buffer))) {
			body.append(buffer, file.gcount());
		}
		if (file.gcount() > 0) {
			body.append(buffer, file.gcount());
		}
		std::string mimeType = getMimeType(filePath);
		HttpResponse response;
		response.setStatusCode(200);
		response.setBody(body);
		response.setHeader("Content-Type", mimeType);
		response.setHeader("Content-Length", intToString(body.size()));
		response.setHeader("Content-Disposition", "attachment; filename=\"lyrics.pdf\"");
		accumulatedResponses.push_back(response.toString());
		return;
	}
	if (path.find("/download/") == 0) {
		std::string fileName = path.substr(10);
		std::string filePath = "uploads/" + fileName;

		std::cout << "📂 Téléchargement du fichier: " << fileName << std::endl;

		struct stat fileStat;
		if (stat(filePath.c_str(), &fileStat) != 0) {
			HttpResponse response = errorHandler.generateErrorResponse(404);
			accumulatedResponses.push_back(response.toString());
			return;
		}

		if (access(filePath.c_str(), R_OK) != 0) {
			HttpResponse response = errorHandler.generateErrorResponse(403);
			accumulatedResponses.push_back(response.toString());
			return;
		}

		std::ifstream file(filePath.c_str(), std::ios::binary);
		if (!file) {
			HttpResponse response = errorHandler.generateErrorResponse(500);
			accumulatedResponses.push_back(response.toString());
			return;
		}

		std::string mimeType = getMimeType(filePath);
		HttpResponse response;
		response.setStatusCode(200);
		response.setHeader("Content-Type", mimeType);
		response.setHeader("Content-Length", intToString(fileStat.st_size));
		response.setHeader("Content-Disposition", "attachment; filename=\"" + fileName + "\"");

		accumulatedResponses.push_back(response.toString());

		char buffer[4096];
		while (file.read(buffer, sizeof(buffer))) {
			std::string chunk(buffer, file.gcount());
			accumulatedResponses.push_back(chunk);
		}
		if (file.gcount() > 0) {
			std::string chunk(buffer, file.gcount());
			accumulatedResponses.push_back(chunk);
		}
		return;
	}
	if (path == "/list-uploads") {
		DIR *dir;
		struct dirent *ent;
		std::string json = "[";

		if ((dir = opendir("uploads/")) != NULL) {

			while ((ent = readdir(dir)) != NULL) {
				std::string fileName = ent->d_name;
				if (fileName != "." && fileName != "..") {
					if (json.size() > 1) json += ",";
					json += "\"" + fileName + "\"";
				}
			}
			closedir(dir);
		} else {
			HttpResponse response = errorHandler.generateErrorResponse(500);
			accumulatedResponses.push_back(response.toString());
			return;
		}

		json += "]";

		HttpResponse response;
		response.setStatusCode(200);
		response.setHeader("Content-Type", "application/json");
		response.setHeader("Content-Length", intToString(json.size()));
		response.setBody(json);

		accumulatedResponses.push_back(response.toString());
		return;
	}

	std::string filePath;
    if (location) {
        if (!location->root.empty()) {
            filePath = location->root;
        } else {
            filePath = root;
        }

        if (!location->redirect_url.empty()) {
            HttpResponse response(302);
            response.setHeader("Location", location->redirect_url);
            accumulatedResponses.push_back(response.toString());
            return;
        }

        if (!location->index.empty() && (path == location->path || path == (location->path + "/"))) {
            filePath += "/" + location->index;
        } else {
            filePath += path.substr(location->path.length());
        }
		struct stat fileStat;
		if (stat(filePath.c_str(), &fileStat) == 0) {
			if (S_ISDIR(fileStat.st_mode)) {
				if (location->autoindex) {
					std::string body = generateDirectoryListing(filePath);
					if (!body.empty()) {
						HttpResponse response;
						response.setStatusCode(200);
						response.setBody(body);
						response.setHeader("Content-Type", "text/html");
						response.setHeader("Content-Length", intToString(body.size()));
						accumulatedResponses.push_back(response.toString());
						return;
					}
				} else {
					std::cout << "rentre" << std::endl;
					HttpResponse response = errorHandler.generateErrorResponse(403);
					accumulatedResponses.push_back(response.toString());
					return;
				}
			}
		}
    } else {
		filePath = selectedServer->root + (path == "/" ? "/" + selectedServer->index : path);
    }
	
    struct stat fileStat;
    if (stat(filePath.c_str(), &fileStat) != 0) {
		HttpResponse response = errorHandler.generateErrorResponse(404);
        accumulatedResponses.push_back(response.toString());
        return;
    }

    if (access(filePath.c_str(), R_OK) != 0) {
        HttpResponse response = errorHandler.generateErrorResponse(403);
        accumulatedResponses.push_back(response.toString());
        return;
    }

    std::ifstream file(filePath.c_str(), std::ios::binary);
    if (!file) {
		HttpResponse response = errorHandler.generateErrorResponse(500);
        accumulatedResponses.push_back(response.toString());
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string body = buffer.str();

    HttpResponse response;
    response.setStatusCode(200);
    response.setBody(body);
    response.setHeader("Content-Type", getMimeType(filePath));
    response.setHeader("Content-Length", intToString(body.size()));

    accumulatedResponses.push_back(response.toString());
}


void WebServer::handlePost(int clientFd, const HttpRequest &httpRequest, int port) {
    std::cout << "📥 Requête reçue : POST " << httpRequest.getPath() << std::endl;

    std::string contentType = httpRequest.getHeader("Content-Type");
    std::string body = httpRequest.getBody();
    
    ServerConfig* selectedServer = NULL;
    std::vector<ServerConfig> servers = config.getServers();
    for (size_t i = 0; i < servers.size(); ++i) {
        if (std::find(servers[i].ports.begin(), servers[i].ports.end(), port) != servers[i].ports.end()) {
            selectedServer = &servers[i];
            break;
        }
    }

    if (!selectedServer) {
        std::cerr << "❌ Serveur non trouvé pour le port " << port << std::endl;
        return;
    }

    int maxBodySize = selectedServer->client_max_body_size * 1024 * 1024;

    if (static_cast<int>(body.size()) > maxBodySize) {
        std::cerr << "❌ Corps de la requête trop volumineux" << std::endl;
        HttpResponse response = errorHandler.generateErrorResponse(413);
        accumulatedResponses.push_back(response.toString());
        return;
    }

    if (contentType.find("application/x-www-form-urlencoded") != std::string::npos) {
        std::cout << "✅ Formulaire classique (x-www-form-urlencoded)" << std::endl;
        FormDataHandler formDataHandler;
        formDataHandler.saveFormData(body);
    } else if (contentType.find("multipart/form-data") != std::string::npos) {
        std::cout << "✅ Formulaire avec fichiers (multipart/form-data)" << std::endl;
        FormDataHandler formDataHandler;
        formDataHandler.handleMultipartFormData(body, contentType, clientFd);
    } else if (contentType.find("text/plain") != std::string::npos) {
        std::cout << "✅ Formulaire avec texte brut (text/plain)" << std::endl;
        std::ofstream outFile("./uploads/received_text.txt");
        if (outFile.is_open()) {
            outFile << body;
            outFile.close();
            std::cout << "Texte stocké dans 'received_text.txt'" << std::endl;
        } else {
            std::cerr << "❌ Impossible d'ouvrir le fichier pour écrire" << std::endl;
        }
    } else {
        std::cerr << "❌ Mauvais Content-Type" << std::endl;
        HttpResponse response = errorHandler.generateErrorResponse(415);
        accumulatedResponses.push_back(response.toString());
        return;
    }

    HttpResponse response;
    response.setStatusCode(200);
    response.setHeader("Content-Type", "application/json");
    response.setBody("{\"success\": true}");
    accumulatedResponses.push_back(response.toString());
}

void WebServer::handleDelete(const std::string &path) {
	std::cout << "📥 Requête reçue : DELETE " << path << std::endl;
	
	if (path.find("/contact") != 0 && path.find("/uploads") != 0) {
		HttpResponse response = errorHandler.generateErrorResponse(400);
		response.setHeader("Content-Type", "application/json");
		response.setBody("{\"error\": \"Mauvais chemin\"}");
		accumulatedResponses.push_back(response.toString());
		return;
	}

	std::string filePath;
	if (path.find("/contact") == 0) {
		filePath = "contact" + path.substr(8);
	} else if (path.find("/uploads") == 0) {
		filePath = "uploads" + path.substr(8);
	}

	std::cout << "🔍 Tentative de suppression du fichier: " << filePath << std::endl;

	struct stat fileStat;
	if (stat(filePath.c_str(), &fileStat) != 0) {
		HttpResponse response = errorHandler.generateErrorResponse(404);
		accumulatedResponses.push_back(response.toString());
		return;
	}

	if (remove(filePath.c_str()) != 0) {
		std::cerr << "❌ Erreur lors de la suppression du fichier: " << filePath << std::endl;
		HttpResponse response = errorHandler.generateErrorResponse(500);
		accumulatedResponses.push_back(response.toString());
		return;
	}
	
	std::cout << "✅ Fichier supprimé avec succès: " << filePath << std::endl;

	HttpResponse response;
	response.setStatusCode(200);
	response.setHeader("Content-Type", "application/json");
	response.setBody("{\"success\": true, \"message\": \"Fichier supprimé avec succès\"}");
	accumulatedResponses.push_back(response.toString());
}

void WebServer::stop(){
	if(running) {
		running = false;
		close(epoll_fd);
		std::cout << "Server stopped cleanly.\n";
	}
}

int WebServer::getHeadersSize(const std::string &request) const {
	const char *endOfHeaders = strstr(request.c_str(), "\r\n\r\n");
	return endOfHeaders ? endOfHeaders - request.c_str() + 4 : 0;
}

std::string WebServer::getHeader(const std::string &request, const std::string &headerName) const {
	std::string search = headerName + ": ";
	std::size_t pos = request.find(search);
	if (pos != std::string::npos) {
		std::size_t start = pos + search.size();
		std::size_t end = request.find("\r\n", start);
		return request.substr(start, end - start);
	}
	return "";
}