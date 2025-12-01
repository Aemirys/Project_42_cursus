/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:51:35 by estosche          #+#    #+#             */
/*   Updated: 2025/03/04 10:55:50 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <string>
#include <cstdlib>
#include <map>
#include <sstream>
#include <iostream>
#include <vector>

class HttpRequest{
	public:
		std::string method;
		std::string path;
		std::string httpVersion;
		std::map<std::string, std::string> headers;
		std::string body;
		HttpRequest();
		~HttpRequest();
		std::string headersToString() const;
		bool parse(const std::string& rawRequest);
		std::string getPath() const;
		std::string getMethod() const;
		std::string getBody() const;
		std::string getHeader(const std::string &key) const;
		std::map<std::string, std::string> getHeaders() const;
		std::string getBoundary() const;
		std::map<std::string, std::string> parseMultipart(const std::string &boundary) const;
		std::string getQueryString() const;
};

#endif