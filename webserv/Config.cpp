/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:59:42 by estosche          #+#    #+#             */
/*   Updated: 2025/03/11 14:02:40 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::Config() {}

Config::~Config() {}

void trim(std::string& str) {
	size_t start = str.find_first_not_of(" \t");
	if (start != std::string::npos) {
		str = str.substr(start);
	}

	size_t end = str.find_last_not_of(" \t");
	if (end != std::string::npos) {
		str = str.substr(0, end + 1);
	} else {
		str = "";
	}
}

std::string Config::getRoot() const {
	return servers.empty() ? "" : servers[0].root;
}

std::string Config::getAdmin() const {
	return servers.empty() ? "" : servers[0].server_name; 
}

std::vector<int> Config::getPorts() const {
	std::vector<int> all_ports;
	for (size_t i = 0; i < servers.size(); ++i) {
		for (size_t j = 0; j < servers[i].ports.size(); ++j) {
			all_ports.push_back(servers[i].ports[j]);
		}
	}
	return all_ports;
}

std::vector<ServerConfig> Config::getServers() const {
	return servers;
}

std::string Config::getCgiPass(const std::string& locationPath) const {
    for (std::vector<ServerConfig>::const_iterator serverIt = servers.begin(); serverIt != servers.end(); ++serverIt) {
        const ServerConfig& server = *serverIt;

        for (std::vector<LocationConfig>::const_iterator locationIt = server.locations.begin(); locationIt != server.locations.end(); ++locationIt) {
            const LocationConfig& location = *locationIt;

            if (location.path == locationPath) {
                return location.cgi_pass;
            }
        }
    }
    return "";
}

std::string Config::getIndex(const std::string& locationPath) const {
    for (std::vector<ServerConfig>::const_iterator serverIt = servers.begin(); serverIt != servers.end(); ++serverIt) {
        const ServerConfig& server = *serverIt;
        for (std::vector<LocationConfig>::const_iterator locationIt = server.locations.begin(); locationIt != server.locations.end(); ++locationIt) {
            const LocationConfig& location = *locationIt;
            if (location.path == locationPath) {
                return location.index;
            }
        }
    }
    return "";
}

bool Config::loadConfig(const std::string& filename) {
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		std::cerr << "Error opening config file" << std::endl;
		return false;
	}

	std::string line;
	ServerConfig* current_server = NULL;
	LocationConfig* current_location = NULL;

	while (std::getline(file, line)) {
		trim(line);
		if (line.empty() || line[0] == '#') continue;

		if (line.find("server {") != std::string::npos) {
			servers.push_back(ServerConfig());
			current_server = &servers.back();
			current_location = NULL;
		} 
		else if (line.find("location ") != std::string::npos) {
			if (!current_server) {
				std::cerr << "Error: location outside of server block" << std::endl;
				continue;
			}
			size_t start = line.find("location ") + 9;
			size_t end = line.find("{");
			if (end == std::string::npos || start >= line.size()) {
				std::cerr << "Error: malformed location block" << std::endl;
				continue;
			}
			std::string path = line.substr(start, end - start);
			trim(path);
			current_server->locations.push_back(LocationConfig());
			current_location = &current_server->locations.back();
			current_location->path = path;
		} 
		else if (line.find("}") != std::string::npos) {
			current_location = NULL;  
		} 
		else if (current_server) {
			parseLine(line, *current_server, current_location);
		}
	}
	
	file.close();
	return true;
}

std::map<int, std::string> Config::getErrorPages() const {
	std::map<int, std::string> allErrorPages;
	for (std::vector<ServerConfig>::const_iterator it = servers.begin(); it != servers.end(); ++it) {
		const ServerConfig& server = *it;
		allErrorPages.insert(server.error_pages.begin(), server.error_pages.end());
	}
	return allErrorPages;
}

std::set<std::string> Config::getAllowedMethods(const std::string& path) const {
    std::set<std::string> methods;
    for (size_t i = 0; i < servers.size(); i++) {
        const ServerConfig& server = servers[i];

        for (size_t j = 0; j < server.locations.size(); j++) {
            if (server.locations[j].path == path) {
                methods.insert(server.locations[j].allowed_methods.begin(), server.locations[j].allowed_methods.end());
                return methods;
            }
        }

        methods.insert(server.allowed_methods.begin(), server.allowed_methods.end());
        return methods;
    }
    return methods;
}


void Config::parseLine(const std::string& line, ServerConfig& server, LocationConfig* location) {
    size_t pos = line.find(" ");
    if (pos == std::string::npos) return;

    std::string key = line.substr(0, pos);
    std::string value = line.substr(pos + 1);
    trim(value);

    if (key == "listen") {
        std::istringstream ss(value);
        std::string port;
        while (ss >> port) {
            server.ports.push_back(atoi(port.c_str()));
        }
    }
    else if (key == "server_name") {
        server.server_name = value;
    }
    else if (key == "root") {
        if (location) location->root = value;
        else server.root = value;
    }
    else if (key == "index") {
        if (location) location->index = value;
        else server.index = value;
    }
    else if (key == "client_max_body_size") {
        int size = atoi(value.c_str());
        if (location) location->client_max_body_size = size;
        else server.client_max_body_size = size;
    }
    else if (key == "cgi_pass" && location) {
        location->cgi_pass = value;
    }
    else if (key == "autoindex" && location) {
        location->autoindex = (value == "on" || value == "true");
    }
    else if (key.find("error_page") != std::string::npos) {
        std::string error_code_str = value;
        trim(error_code_str);

        size_t pos = error_code_str.find(" ");
        if (pos == std::string::npos) {
            std::cerr << "Error: malformed error_page value, no error code found." << std::endl;
            return;
        }
        std::string error_code_part = error_code_str.substr(0, pos);
        std::string error_page_path = error_code_str.substr(pos + 1);

        bool is_valid_code = true;
        for (size_t i = 0; i < error_code_part.size(); i++) {
            if (!isdigit(error_code_part[i])) {
                is_valid_code = false;
                break;
            }
        }

        if (is_valid_code && !error_code_part.empty()) {
            int error_code = atoi(error_code_part.c_str());

            if (error_code >= 400 && error_code <= 599) {
                server.error_pages[error_code] = error_page_path;
            } else {
                std::cerr << "Error: invalid HTTP error code: " << error_code << std::endl;
            }
        } else {
            std::cerr << "Error: malformed error_page value, invalid or missing error code." << std::endl;
        }
    }
    else if (key == "allow") {
        if (location) location->allow_ips.push_back(value);
    }
    else if (key == "deny" && value == "all") {
        if (location) location->deny_all = true;
    }
    else if (key == "return") {
        if (location) location->redirect_url = value;
    }
    else if (key == "limit_except") {
        std::istringstream ss(value);
        std::string method;
        while (std::getline(ss, method, ' ')) {
            trim(method);
            if (!method.empty()) {
                if (location)
                    location->allowed_methods.push_back(method);
                else
                    server.allowed_methods.push_back(method);
            }
        }
    }
}