/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FormDataHandler.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:55:09 by estosche          #+#    #+#             */
/*   Updated: 2025/03/04 13:56:15 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_DATA_HANDLER_HPP
#define FORM_DATA_HANDLER_HPP

#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <sys/socket.h>
#include "MultipartParser.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "ErrorHandler.hpp"
#include <unistd.h>


class FormDataHandler {
	public:
		std::string generateUniqueFilename();
		std::string decodeUrlEncoded(const std::string& encoded);
		void saveFormParam(std::ofstream &outFile, const std::string& param);
		void saveFormData(const std::string& body);
		void handleMultipartFormData(const std::string& body, const std::string& contentType, int clientFd);
};

#endif
