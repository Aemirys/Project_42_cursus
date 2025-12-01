/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigValidator.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:37:57 by estosche          #+#    #+#             */
/*   Updated: 2025/03/11 14:03:10 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigValidator.hpp"


ConfigValidator::ConfigValidator(const Config& config) : config(config) {}


bool ConfigValidator::validate() {

    if (!validatePorts()) {
        return false;
    }

    if (!validateErrorPages()) {
        return false;
    }

    if (!validateAllowedMethods()) {
        return false;
    }

    return true;
}

bool ConfigValidator::validatePorts() {
    std::vector<int> ports = config.getPorts();
    std::set<int> uniquePorts;
    for (std::vector<int>::iterator it = ports.begin(); it != ports.end(); ++it) {
        int port = *it;
        if (uniquePorts.find(port) != uniquePorts.end()) {
            std::cerr << "Error: Duplicate port found: " << port << std::endl;
            return false;
        }
        uniquePorts.insert(port);
    }
    return true;
}

bool ConfigValidator::validateErrorPages() {
    std::map<int, std::string> errorPages = config.getErrorPages();
    for (std::map<int, std::string>::iterator it = errorPages.begin(); it != errorPages.end(); ++it) {
        int errorCode = it->first;
        std::string pagePath = it->second;
        if (pagePath.empty()) {
            std::cerr << "Error: No page path defined for error code " << errorCode << std::endl;
            return false;
        }
    }
    return true;
}

bool ConfigValidator::validateAllowedMethods() {
    const std::vector<ServerConfig>& servers = config.getServers();
    for (size_t i = 0; i < servers.size(); i++) {
        const ServerConfig& server = servers[i];
        for (size_t j = 0; j < server.locations.size(); j++) {
            const LocationConfig& location = server.locations[j];
            if (location.allowed_methods.empty()) {
                std::cerr << "Error: No allowed methods defined for location: " << location.path << std::endl;
                return false;
            }
        }
    }
    return true;
}
