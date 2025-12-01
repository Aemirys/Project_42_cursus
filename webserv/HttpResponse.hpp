/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:30:53 by estosche          #+#    #+#             */
/*   Updated: 2025/03/10 16:12:06 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <string>
#include <map>
#include <sstream>

class HttpResponse {
	public:
		HttpResponse(int statusCode = 200, const std::string& statusMessage = "OK", const std::string& body = "");
		void setHeader(const std::string& key, const std::string& value);
		void setBody(const std::string& body);
		int getStatusCode() const { return statusCode; }
		std::string getStatusMessage() const { return statusMessage; }
		std::string getBody() const { return body; }
		std::string getHeaders() const;
		void setStatusCode(int code);
		std::string getBodyLength() const;
		std::string toString() const;
		std::string getStatusMessageForCode(int code);
	private:
		int statusCode;
		std::string statusMessage;
		std::string body;
		std::map<std::string, std::string> headers;   
	};
	
#endif
