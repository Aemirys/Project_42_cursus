/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:59:42 by estosche          #+#    #+#             */
/*   Updated: 2025/02/05 15:08:53 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <locale>

static inline void trim(std::string& str) {
	size_t first = str.find_first_not_of(" \t\n\r");
	if (first != std::string::npos) {
		str = str.substr(first);
	} else {
		str.clear();
	}

	// Supprimer les espaces à la fin
	size_t last = str.find_last_not_of(" \t\n\r");
	if (last != std::string::npos) {
		str = str.substr(0, last + 1);
	} else {
		str.clear();
	}
}

Config::Config() : root("./") {}

bool Config::loadConfig(const std::string& filename){
	std::ifstream file(filename.c_str());
	if(!file.is_open()){
		std::cerr << "Error opening config file" << std::endl;
		return false;
	}
	std::string line;
	while(std::getline(file, line)){
		parseLine(line);
	}
	file.close();
	return true;
}

void Config::parseLine(const std::string& line) {
    if (line.find("port") != std::string::npos) {
        // Lister les ports séparés par des virgules
        std::string port_list = line.substr(line.find("=") + 1);
        trim(port_list);
        std::stringstream ss(port_list);
        std::string port_str;
        while (std::getline(ss, port_str, ',')) {
            trim(port_str);
            int port = std::atoi(port_str.c_str());  // Convertir en entier
            ports.push_back(port);  // Ajouter à la liste des ports
        }
    }
	else if (line.find("error_page_403") != std::string::npos) {
        error_page_403 = line.substr(line.find("=") + 1);
        trim(error_page_404);
    }
    else if (line.find("error_page_404") != std::string::npos) {
        error_page_404 = line.substr(line.find("=") + 1);
        trim(error_page_404);
    }
    else if (line.find("error_page_500") != std::string::npos) {
        error_page_500 = line.substr(line.find("=") + 1);
        trim(error_page_500);
    }
    else if (line.find("error_page_503") != std::string::npos) {
        error_page_503 = line.substr(line.find("=") + 1);
        trim(error_page_503);
    }
    else if (line.find("root") != std::string::npos) {
        root = line.substr(line.find("=") + 1);
        trim(root);
    }
	else if (line.find("admin") != std::string::npos) {
        admin = line.substr(line.find("=") + 1);
        trim(root);
    }
    else if (line.find("allowed_methods") != std::string::npos) {
        std::string methods = line.substr(line.find("=") + 1);
        trim(methods);
        std::stringstream ss(methods);
        std::string method;
        while (std::getline(ss, method, ',')) {
            trim(method);
            allowed_methods.push_back(method);
        }
    }
}

std::vector<int> Config::getPorts(int& num_ports) {
    static int ports[] = {8080, 8070}; // Définition statique des ports
    num_ports = sizeof(ports) / sizeof(ports[0]);  // Calcul du nombre de ports

    // Convertir le tableau statique en std::vector
    return std::vector<int>(ports, ports + num_ports);
}

int Config::getPort() const {
	if (!ports.empty()) {
        return ports[0];
    }
    return 8080;
}

std::string Config::getRoot() const{
	return root;
}

std::string Config::getErrorPage403() const{
	return error_page_403;
}

std::string Config::getErrorPage404() const{
	return error_page_404;
}

std::string Config::getErrorPage405() const{
	return error_page_405;
}

std::string Config::getErrorPage500() const{
	return error_page_500;
}

std::string Config::getErrorPage503() const{
	return error_page_503;
}

std::string Config::getAdmin() const{
	return admin;
}

std::vector<std::string> Config::getAllowedMethods() const{
	return allowed_methods;
}