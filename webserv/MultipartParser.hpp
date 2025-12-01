/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MultipartParser.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:26:09 by estosche          #+#    #+#             */
/*   Updated: 2025/03/04 11:02:30 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTIPARTPARSER_HPP
#define MULTIPARTPARSER_HPP

#include <string>
#include <map>
#include <vector>
#include <fstream>

class MultipartParser {
	public:
		MultipartParser(const std::string &contentType, const std::string &body);
		void parse(int clientFd);
		std::map<std::string, std::string> getFormFields() const;
		std::map<std::string, std::string> getFileFields() const;
		std::string getFileExtension(const std::string &mimeType);
		std::string getFileExtensionFromMimeType(const std::string &mimeType);

	private:
		std::string contentType;
		std::string body;
		std::string boundary;
		std::vector<std::string> parts;
		std::map<std::string, std::string> formFields;
		std::map<std::string, std::string> fileFields;

		std::string extractBoundary();
		std::vector<std::string> splitMultipartBody();
		std::string extractFileName(const std::string &part);
		std::string extractFileContent(const std::string &part);
		std::string extractMimeType(const std::string &part);
		static std::map<std::string, std::string> initializeMimeTypeMap();
		static std::map<std::string, std::string> mimeTypeMap;
};

#endif