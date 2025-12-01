/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:33:05 by estosche          #+#    #+#             */
/*   Updated: 2025/03/10 17:08:16 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include "FormDataHandler.hpp"
#include "MultipartParser.hpp"
#include "CgiHandler.hpp"
#include "utils.hpp"
#include "Config.hpp"
#include "HttpRequest.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdio>
#include <csignal>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <map>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <cstring>

class WebServer{
	private:
		Config config;
		ErrorHandler errorHandler;
		std::map<int, int> client_ports;
		std::string root;
		std::string errorPage403;
		std::string errorPage404;
		std::string errorPage405; 
		std::string errorPage500;
		std::string errorPage503;
		int epoll_fd;
		bool running;
		std::string admin;
		std::map<std::string, std::string> locationIndexes;
		int client_max_body_size;
		std::vector<int> ports;
		std::vector<std::string> accumulatedResponses;
		void handleClient(int client_fd);
		std::string getMimeType(const std::string& path);
		std::string getApiIndexFromLocation(const std::string &path);
		std::string getHeader(const std::string &request, const std::string &headerName) const;
		int getHeadersSize(const std::string &request) const;

	public:
		int event_fd;
		WebServer(const Config& config);
		~WebServer();
		int create_and_add_server_socket(int port);
		void handleRequest(int clientFd, const std::string &request, int clientPort);
		void handleGet(const std::string &path, int port);
		void handlePost(int clientFd, const HttpRequest &httpRequest, int clientPort);
		void handleDelete(const std::string &path);
		void handleCgiRequest(const char* path, const char* cgiExecutable, const char* method, const char* queryString, const char* body);
		void start();
		void stop();
		void sendAccumulatedResponses(int clientFd);
		int writeFileChunk(const char* buffer, int bytesRead);
};

#endif