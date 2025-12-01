/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:29:54 by estosche          #+#    #+#             */
/*   Updated: 2025/03/04 13:54:39 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpResponse.hpp"

HttpResponse::HttpResponse(int statusCode, const std::string& statusMessage, const std::string& body) {

	setStatusCode(statusCode);
	if (statusMessage.empty() || statusMessage == "OK") {
		this->statusMessage = getStatusMessageForCode(statusCode);
	} else {
		this->statusMessage = statusMessage;
	}
	this->body = body;
}

void HttpResponse::setStatusCode(int code) {
	statusCode = code;
	statusMessage = getStatusMessageForCode(code);
}

std::string HttpResponse::getStatusMessageForCode(int code) {
	switch (code) {
			case 200: return "OK";
			case 302: return "Found";
			case 400: return "Bad Request";
			case 403: return "Forbidden";
			case 404: return "Not Found";
			case 405: return "Method Not Allowed";
			case 500: return "Internal Server Error";
			case 503: return "Service Unavailable";
			default: return "OK";
		}
}

std::string HttpResponse::getHeaders() const {
	std::ostringstream headers;
	headers << "HTTP/1.1 " << statusCode << " " << statusMessage << "\r\n";
	headers << "Content-Length: " << body.size() << "\r\n";
	headers << "Content-Type: text/html\r\n\r\n";
	return headers.str();
}

std::string HttpResponse::getBodyLength() const {
	std::ostringstream oss;
	oss << body.size();
	return oss.str();
}

void HttpResponse::setHeader(const std::string& key, const std::string& value) {
	headers[key] = value;
}

void HttpResponse::setBody(const std::string& body) {
	this->body = body;
}

std::string HttpResponse::toString() const {
	std::stringstream response;

	std::map<int, std::string> statusMessages;
	statusMessages[200] = "OK";
	statusMessages[302] = "Found";
	statusMessages[400] = "Bad Request";
	statusMessages[403] = "Forbidden";
	statusMessages[404] = "Not Found";
	statusMessages[405] = "Method Not Allowed";
	statusMessages[413] = "Payload Too Large";
	statusMessages[500] = "Internal Server Error";
	statusMessages[503] = "Service Unavailable";

	std::string statusMessage = statusMessages.count(statusCode) ? statusMessages[statusCode] : "Unknown Status";

	response << "HTTP/1.1 " << statusCode << " " << statusMessage << "\r\n";

	if (headers.find("Content-Length") == headers.end()) {
		response << "Content-Length: " << body.size() << "\r\n";
	}

	if (headers.find("Content-Type") == headers.end()) {
		response << "Content-Type: text/html\r\n";
	}

	for (std::map<std::string, std::string>::const_iterator it = headers.begin(); it != headers.end(); ++it) {
		response << it->first << ": " << it->second << "\r\n";
	}

	response << "\r\n" << body;
	return response.str();
}