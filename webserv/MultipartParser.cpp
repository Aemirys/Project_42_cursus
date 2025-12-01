/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MultipartParser.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:26:41 by estosche          #+#    #+#             */
/*   Updated: 2025/03/05 10:38:02 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MultipartParser.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "ErrorHandler.hpp"

#include <cstring>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>

MultipartParser::MultipartParser(const std::string &contentType, const std::string &body)
	: contentType(contentType), body(body), boundary(extractBoundary()) {}

std::map<std::string, std::string> MultipartParser::initializeMimeTypeMap() {
	std::map<std::string, std::string> map;
	map["text/plain"] = ".txt";
	map["application/pdf"] = ".pdf";
	map["image/png"] = ".png";
	map["image/jpeg"] = ".jpg";
	map["application/zip"] = ".zip";
	map["application/json"] = ".json";
	map["application/msword"] = ".doc";
	map["application/vnd.ms-excel"] = ".xls";
	map["application/vnd.openxmlformats-officedocument.wordprocessingml.document"] = ".docx";
	map["application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"] = ".xlsx";
	map["video/mp4"] = ".mp4";
	map["video/mpeg"] = ".mpeg";
	map["video/ogg"] = ".ogv";
	map["video/webm"] = ".webm";
	map["video/quicktime"] = ".mov";
	map["audio/mpeg"] = ".mp3";
	map["audio/wav"] = ".wav";
	map["audio/ogg"] = ".ogg";
	map["audio/flac"] = ".flac";
	return map;
}

std::map<std::string, std::string> MultipartParser::mimeTypeMap = initializeMimeTypeMap();

std::string MultipartParser::getFileExtensionFromMimeType(const std::string &mimeType) {
	std::map<std::string, std::string>::iterator it = mimeTypeMap.find(mimeType);
	if (it != mimeTypeMap.end()) {
		return it->second;
	} else {
		std::cerr << "❌ Type MIME non reconnu, tentative d'extension par défaut." << std::endl;
		return "";
	}
}

bool fileExists(const std::string& filePath) {
	return access(filePath.c_str(), F_OK) != -1;
}

void MultipartParser::parse(int clientFd) {
	
	if (body.empty()) {
		std::cerr << "❌ Erreur : Le body est vide !" << std::endl;
		return;
	}

	parts = splitMultipartBody();

	for (size_t i = 0; i < parts.size(); ++i) {
		const std::string &part = parts[i];

		if (part.find("Content-Disposition: form-data; name=\"file\"") != std::string::npos) {
			
			std::string fileName = extractFileName(part);
			std::string fileContent = extractFileContent(part);
			std::string mimeType = extractMimeType(part);
			std::string fileExtension = getFileExtensionFromMimeType(mimeType);

			if (fileExtension.empty()) {
				std::cerr << "❌ Erreur : Type MIME inconnu ou non pris en charge (" << mimeType << ")." << std::endl;
				continue;
			}

			std::string finalFileName = fileName.empty() ? "uploaded_file" : fileName;

			std::ostringstream ss;
			ss << clientFd;
			std::string filePath = "uploads/" + ss.str() + "_" + finalFileName;

			std::ofstream file(filePath.c_str(), std::ios::binary);
			if (file) {
				file.write(fileContent.c_str(), fileContent.size());
				file.close();
				std::cout << "✅ Fichier sauvegardé : " << filePath << std::endl;
			} else {
				std::cerr << "❌ Erreur lors de la sauvegarde du fichier : " << filePath << std::endl;
			}

			fileFields[fileName] = fileContent;
		}
	}
}

std::map<std::string, std::string> MultipartParser::getFormFields() const {
	return formFields;
}

std::map<std::string, std::string> MultipartParser::getFileFields() const {
	return fileFields;
}

std::string MultipartParser::extractBoundary() {
	std::string boundary = "";
	size_t pos = contentType.find("boundary=");
	if (pos != std::string::npos) {
		boundary = contentType.substr(pos + 9);
		
		if (boundary.substr(0, 2) == "--") {
			boundary = boundary.substr(4);
		}
	}
	return boundary;
}

std::vector<std::string> MultipartParser::splitMultipartBody() {
	std::vector<std::string> parts;

	std::string delimiter = "------" + boundary;
	std::string endDelimiter = delimiter + "--";

	size_t startPos = 0;
	size_t endPos = 0;
	
	while (startPos < body.size() && body.substr(startPos, delimiter.length()) != delimiter) {
		++startPos;
	}

	if (startPos >= body.size()) {
		std::cout << "[ERROR] Boundary non trouvé dans le body." << std::endl;
		return parts;
	}

	startPos += delimiter.length();
	endPos += endDelimiter.length();
	while (startPos < body.size()) {
		endPos = body.size() - endPos;

		if (endPos == std::string::npos) {
			std::cout << "Fin du body atteinte sans délimiteur de fin." << std::endl;
			break;
		}

		std::string part = body.substr(startPos, endPos - (startPos + 3));

		if (part.substr(part.length() - 2) == "--") {
			part = part.substr(0, part.length() - 2);
		}

		if (part.length() > 0 && part[part.length() - 1] == '\n') {
			part = part.substr(0, part.length() - 1);
		}

		parts.push_back(part);

		startPos = endPos + endDelimiter.length();
	}

	return parts;
}

std::string MultipartParser::extractFileName(const std::string &part) {
	size_t pos = part.find("filename=\"");
	if (pos != std::string::npos) {
		size_t startPos = pos + 10;
		size_t endPos = part.find("\"", startPos);
		if (endPos != std::string::npos) {
			return part.substr(startPos, endPos - startPos);
		}
	}
	return "";
}

std::string MultipartParser::extractFileContent(const std::string &part) {
	size_t startPos = part.find("\r\n\r\n");
	if (startPos == std::string::npos) {
		return "";
	}

	startPos += 4;

	size_t endPos = part.find("\r\n--" + boundary, startPos);
	if (endPos == std::string::npos) {
		return part.substr(startPos);
	}

	return part.substr(startPos, endPos - startPos);
}

std::string MultipartParser::extractMimeType(const std::string &part) {
	size_t pos = part.find("Content-Type: ");
	if (pos != std::string::npos) {
		size_t startPos = pos + 14;
		size_t endPos = part.find("\r\n", startPos);
		if (endPos != std::string::npos) {
			return part.substr(startPos, endPos - startPos);
		}
	}
	return "";
}

std::string MultipartParser::getFileExtension(const std::string &mimeType) {
	if (mimeType == "text/plain") {
		return ".txt";
	} else if (mimeType == "application/pdf") {
		return ".pdf";
	} else {
		return "";
	}
}