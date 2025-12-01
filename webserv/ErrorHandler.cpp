/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:25:59 by estosche          #+#    #+#             */
/*   Updated: 2025/03/10 17:10:47 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorHandler.hpp"


HttpResponse ErrorHandler::generateErrorResponse(int statusCode) {
	HttpResponse response(statusCode);

    std::map<int, std::string> errorPages = config.getErrorPages();
    std::map<int, std::string>::const_iterator it = errorPages.find(statusCode);
    std::string filePath;
	
    if (it != errorPages.end()) {
        filePath = it->second;
    }

    std::ifstream file(filePath.c_str());
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        response.setBody(buffer.str());
    } else {
        std::string defaultError = "<html><body><h1>Error ";
        std::ostringstream oss;
        oss << statusCode;
        defaultError += oss.str();
        defaultError += "</h1><p>The error page for this status code could not be loaded.</p></body></html>";
        response.setBody(defaultError);
    }

    response.setHeader("Content-Type", "text/html");
    std::ostringstream lengthStream;
    lengthStream << response.getBodyLength();
    response.setHeader("Content-Length", lengthStream.str());

    return response;
}