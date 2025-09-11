/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:45:30 by estosche          #+#    #+#             */
/*   Updated: 2025/02/05 14:45:40 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIHANDLER_HPP
#define CGIHANDLER_HPP

#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

class CgiHandler {
public:
    CgiHandler(const std::string &cgiExecutable, const std::string &filePath);
    ~CgiHandler();

    // Méthode pour exécuter le CGI
    std::string executeCgi(const std::string &method, const std::string &body = "");

private:
    std::string cgiExecutable;
    std::string filePath;
    int pipefd[2];  // Pipe pour la communication entre le parent et l'enfant

    void setupPipe();
    void executeScript(const std::string &method, const std::string &body);
    void readOutput(std::string &output);
};

#endif
