/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:45:52 by estosche          #+#    #+#             */
/*   Updated: 2025/03/10 16:04:47 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CgiHandler.hpp"

CgiHandler *CgiHandler::instance = NULL;

CgiHandler::CgiHandler(const char *cgiExecutable, const char *filePath)
	: cgiExecutable(cgiExecutable), filePath(filePath) {
	setupPipe();
    instance = this;
}

CgiHandler::~CgiHandler() {
    instance = NULL;
	close(pipefd[0]);
	close(pipefd[1]);
}

void CgiHandler::setupPipe() {
	if (pipe(pipefd) == -1) {
		std::cerr << "pipe failed" << std::endl;
		exit(1);
	}
}

void CgiHandler::clean(){
    close(pipefd[0]);
    close(pipefd[1]);
    kill(pid, SIGKILL);
}

void CgiHandler::handleAlarm(int sig) {
    (void) sig;
    std::cerr << "Script CGI execution timed out." << std::endl;
    if (instance) {
        instance->clean();
    }
    throw std::runtime_error("CGI script execution timed out");
}

void CgiHandler::executeScript(const char *method, const char *queryString, const char *body) {
    signal(SIGALRM, handleAlarm);
    alarm(5);

    pid = fork();
    if (pid < 0) {
        std::cerr << "❌ Fork failed" << std::endl;
        throw std::runtime_error("Fork error in CGI execution");
    }

    if (pid == 0) { 
        close(pipefd[0]);

        if (strcmp(method, "POST") == 0) {     
			dup2(pipefd[1], STDIN_FILENO);
			ssize_t bytes_written = write(STDIN_FILENO, body, strlen(body));
			if (bytes_written == -1)
			{
				std::cerr << "❌ Error writing in pipe." << std::endl;
			}
			else if (bytes_written < static_cast<ssize_t>(strlen(body)))
			{
				std::cerr << "Not all bytes written in pipe." << std::endl;
			}
			close(pipefd[1]);
		} else {
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}

        char requestMethod[256];
        char scriptFilename[256];
        char contentLength[256];
        char queryStringEnv[256];

        snprintf(requestMethod, sizeof(requestMethod), "REQUEST_METHOD=%s", method);
        snprintf(scriptFilename, sizeof(scriptFilename), "SCRIPT_FILENAME=%s", filePath);
        snprintf(contentLength, sizeof(contentLength), "CONTENT_LENGTH=%zu", strlen(body));
        snprintf(queryStringEnv, sizeof(queryStringEnv), "QUERY_STRING=%s", queryString);

        char *envp[] = {
            requestMethod,
            scriptFilename,
            contentLength,
            queryStringEnv,
            NULL
        };

        char *argv[] = {
            (char *)cgiExecutable,
            (char *)filePath,
            NULL
        };

        execve(cgiExecutable, argv, envp);
        std::cerr << "❌ execve failed" << std::endl;
        exit(1);
    }
}

void CgiHandler::readOutput(std::string &output) {
    char buffer[1024];
    ssize_t bytesRead;

    close(pipefd[1]);


    int flags = fcntl(pipefd[0], F_GETFL, 0);
    if (flags == -1) {
        std::cerr << "❌ Error getting flags " << std::endl;
        return;
    }
    if (fcntl(pipefd[0], F_SETFL, flags | O_NONBLOCK) == -1) {
        std::cerr << "❌ Error setting O_NONBLOCK " << std::endl;
        return;
    }

    while (true) {
        bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            output.append(buffer, bytesRead);
        } else if (bytesRead == 0) {
            break;
        } else {
            usleep(1000);
        }
    }

    if (bytesRead == -1) {
        std::cerr << "❌ Error reading from CGI pipe " << std::endl;
    }

    close(pipefd[0]);
    alarm(0);
}

std::string CgiHandler::executeCgi(const char *method, const char *queryString, const char *body) {
    std::string output;
    int status;

    executeScript(method, queryString, body);
    readOutput(output);

    if (waitpid(pid, &status, 0) == -1) {
        throw std::runtime_error("waitpid failed");
    }

    if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
        throw std::runtime_error("CGI script failed");
    }

    return output;
}