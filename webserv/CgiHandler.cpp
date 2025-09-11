/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:45:52 by estosche          #+#    #+#             */
/*   Updated: 2025/02/10 13:11:30 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CgiHandler.hpp"
#include <cstdio>    // Pour perror
#include <cstdlib>   // Pour exit
#include <unistd.h>  // Pour fork, pipe, execlp, etc.
#include <sys/wait.h> // Pour waitpid

CgiHandler::CgiHandler(const std::string &cgiExecutable, const std::string &filePath)
    : cgiExecutable(cgiExecutable), filePath(filePath) {
    setupPipe();
}

CgiHandler::~CgiHandler() {
    // Fermeture du pipe
    close(pipefd[0]);
    close(pipefd[1]);
}

void CgiHandler::setupPipe() {
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(1);
    }
}

void CgiHandler::executeScript(const std::string &method, const std::string &body) {
    pid_t pid = fork();
    (void) body;
	
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {  // Processus enfant
        close(pipefd[0]);  // Fermer l'extrémité de lecture dans le processus enfant

        // Redirection de la sortie vers le pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        // Créer les variables d'environnement pour CGI
        std::string requestMethod = "REQUEST_METHOD=" + method;
        std::string scriptFilename = "SCRIPT_FILENAME=" + filePath;

        // Créer un tableau d'environnement
        char *envp[] = {
            (char *)requestMethod.c_str(),
            (char *)scriptFilename.c_str(),
            NULL  // Fin du tableau avec NULL
        };

        // if (method == "POST" && !body.empty()) {
        //     // Envoyer les données POST via stdin si elles existent
        //     write(STDIN_FILENO, body.c_str(), body.size());
        // }

        // Utilisation de execle pour inclure l'environnement
        execle(cgiExecutable.c_str(), cgiExecutable.c_str(), filePath.c_str(), (char *)NULL, envp);

        // Si execle échoue, on termine le processus
        perror("execle failed");
        exit(1);
    }
}


void CgiHandler::readOutput(std::string &output) {
    close(pipefd[1]);  // Fermer l'écriture du pipe dans le processus parent

    char buffer[1024];
    ssize_t bytesRead;
	
    // Lire la sortie du script CGI depuis le pipe
    while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
        output.append(buffer, bytesRead);
    }

    close(pipefd[0]);
}

std::string CgiHandler::executeCgi(const std::string &method, const std::string &body) {
    std::string output;
	
    // Lancer le script CGI
    executeScript(method, body);

    // Lire la sortie du script CGI
    readOutput(output);

    // Attendre la fin du processus enfant
    int status;
    waitpid(-1, &status, 0);

    return output;
}
