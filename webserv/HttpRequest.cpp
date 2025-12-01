/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:54:34 by estosche          #+#    #+#             */
/*   Updated: 2025/03/04 10:56:56 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpRequest.hpp"
#include "MultipartParser.hpp"


HttpRequest::HttpRequest() {}

HttpRequest::~HttpRequest() {}

bool HttpRequest::parse(const std::string &rawRequest) {
	
	std::istringstream requestStream(rawRequest);
	std::string line;

	if (!std::getline(requestStream, line) || line.empty()) {
		std::cerr << "Erreur : Ligne de requête invalide." << std::endl;
		return false;
	}

	std::istringstream lineStream(line);
	lineStream >> method >> path;

	while (std::getline(requestStream, line) && !line.empty() && line != "\r") {
		std::size_t pos = line.find(": ");
		if (pos != std::string::npos) {
			std::string key = line.substr(0, pos);
			std::string value = line.substr(pos + 2);
			headers[key] = value;
		}
	}

	std::string contentLengthStr = getHeader("Content-Length");
	int contentLength = contentLengthStr.empty() ? 0 : atoi(contentLengthStr.c_str());
	if (requestStream.peek() == '\r') {
		requestStream.get();
		if (requestStream.peek() == '\n') {
			requestStream.get();
		}
	}
	if (method == "POST" && contentLength > 0) {
		std::vector<char> buffer(contentLength);
		requestStream.read(&buffer[0], contentLength);
		int bytesRead = requestStream.gcount();
		
		if (bytesRead != contentLength) {
			std::cerr << "⚠️ Erreur : Nombre d'octets lus (" << bytesRead
					  << ") ne correspond pas à Content-Length (" << contentLength << ")." << std::endl;
			return false;
		}

		body.assign(buffer.begin(), buffer.end());  
	} 
	return true;
}

std::string HttpRequest::getQueryString() const {
	std::string queryString;
	size_t queryStart = path.find('?');
	if (queryStart != std::string::npos) {
		queryString = path.substr(queryStart + 1);
	}
	return queryString;
}

std::string HttpRequest::getHeader(const std::string &key) const {
	std::map<std::string, std::string>::const_iterator it = headers.find(key);
	if (it != headers.end()) {
		return it->second;
	}
	return "";
}

std::string HttpRequest::getPath() const {
	return path;
}

std::string HttpRequest::getMethod() const {
	return method;
}

std::string HttpRequest::getBody() const {
	return body;
}

std::map<std::string, std::string> HttpRequest::getHeaders() const {
	return headers;
}

std::string HttpRequest::getBoundary() const {
	std::string contentType = getHeader("Content-Type");
	size_t pos = contentType.find("boundary=");
	if (pos != std::string::npos) {
		return "--" + contentType.substr(pos + 9);
	}
	return "";
}

std::map<std::string, std::string> HttpRequest::parseMultipart(const std::string &boundary) const {
	std::map<std::string, std::string> files;
	std::string body = this->getBody();

	size_t pos = 0;
	while ((pos = body.find(boundary, pos)) != std::string::npos) {
		size_t endPos = body.find(boundary, pos + boundary.length());
		if (endPos == std::string::npos) break;

		std::string part = body.substr(pos + boundary.length(), endPos - pos - boundary.length());
		size_t dispoPos = part.find("Content-Disposition:");
		if (dispoPos == std::string::npos) continue;

		size_t filenamePos = part.find("filename=\"", dispoPos);
		if (filenamePos == std::string::npos) continue;
		size_t filenameEnd = part.find("\"", filenamePos + 10);
		std::string filename = part.substr(filenamePos + 10, filenameEnd - (filenamePos + 10));

		size_t dataStart = part.find("\r\n\r\n", filenameEnd);
		if (dataStart == std::string::npos) continue;
		dataStart += 4;

		std::string fileData = part.substr(dataStart);
		files[filename] = fileData;

		pos = endPos;
	}
	return files;
}

std::string HttpRequest::headersToString() const {
	std::string result;
	for (std::map<std::string, std::string>::const_iterator it = headers.begin(); it != headers.end(); ++it) {
		result += it->first + ": " + it->second + "\r\n";
	}
	return result;
}