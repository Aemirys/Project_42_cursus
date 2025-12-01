/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:31:05 by estosche          #+#    #+#             */
/*   Updated: 2025/03/11 13:56:45 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServer.hpp"
#include "Config.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "ErrorHandler.hpp"
#include "ConfigValidator.hpp"
#include "utils.hpp"
#include <cstdlib>
#include <csignal>

WebServer *serverInstance = NULL;

void handleSignal(int signal){
    if(signal == SIGINT) {
        std::cout << "\nServer shutdown requested...\n";
        if (serverInstance != NULL){
            serverInstance->stop();
        }
    }
}

int main(int argc, char **argv) {
    signal(SIGINT, handleSignal);
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return EXIT_FAILURE;
    }

    Config config;
    if (!config.loadConfig(argv[1])) {
        std::cerr << "Error loading configuration file." << std::endl;
        return 1;
    }

    ConfigValidator validator(config);
    if (!validator.validate()) {
        std::cerr << "Configuration validation failed." << std::endl;
        return 1;
    }

    std::cout << "Configuration loaded and validated successfully!" << std::endl;
    WebServer server(config);
    serverInstance = &server;
    server.start();

    return EXIT_SUCCESS;
}