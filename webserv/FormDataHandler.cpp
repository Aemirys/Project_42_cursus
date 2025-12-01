/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FormDataHandler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:55:37 by estosche          #+#    #+#             */
/*   Updated: 2025/03/04 13:53:20 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FormDataHandler.hpp"
#include "MultipartParser.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "ErrorHandler.hpp"


std::string FormDataHandler::generateUniqueFilename() {
	std::time_t now = std::time(0);
	std::stringstream filename;
	filename << "contact/formulaire_" << now << ".txt";
	
	return filename.str();
}

void FormDataHandler::saveFormData(const std::string& body) {
	std::string decodedBody = decodeUrlEncoded(body);
	size_t pos = 0;
	size_t paramPos = 0;

	std::string uniqueFilename = generateUniqueFilename();

	std::ofstream outFile(uniqueFilename.c_str(), std::ios::app);
	if (!outFile) {
		std::cerr << "❌ Impossible d'ouvrir le fichier dans 'contact/'." << std::endl;
		return;
	}
	outFile << std::endl;
	while ((paramPos = decodedBody.find('&', pos)) != std::string::npos) {
		std::string param = decodedBody.substr(pos, paramPos - pos);
		saveFormParam(outFile, param);
		pos = paramPos + 1;
	}
	saveFormParam(outFile, decodedBody.substr(pos));
	outFile << std::endl;
	outFile.close();

	std::cout << "✅ Formulaire enregistré dans " << uniqueFilename << "." << std::endl;
}

std::string FormDataHandler::decodeUrlEncoded(const std::string& encoded) {
	std::string decoded;
	size_t i = 0;

	while (i < encoded.length()) {
		if (encoded[i] == '%') {
			if (i + 2 < encoded.length()) {
				int value;
				std::stringstream ss;
				ss << std::hex << encoded.substr(i + 1, 2);
				ss >> value;
				decoded += static_cast<char>(value);
				i += 3;
			}
		} else if (encoded[i] == '+') {
			decoded += ' ';
			i++;
		} else {
			decoded += encoded[i++];
		}
	}
	return decoded;
}

void FormDataHandler::saveFormParam(std::ofstream &outFile, const std::string& param) {
	size_t separatorPos = param.find('=');
	if (separatorPos != std::string::npos) {
		std::string key = param.substr(0, separatorPos);
		std::string value = param.substr(separatorPos + 1);
		outFile << key << " : " << value << std::endl;
	}
}

void FormDataHandler::handleMultipartFormData(const std::string& body, const std::string& contentType, int clientFd) {
	MultipartParser parser(contentType, body);
	parser.parse(clientFd);
}