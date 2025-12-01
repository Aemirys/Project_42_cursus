/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:45:30 by estosche          #+#    #+#             */
/*   Updated: 2025/03/10 15:53:14 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIHANDLER_HPP
#define CGIHANDLER_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>
#include <cstdio>
#include <stdlib.h>
#include <cstring>
#include <signal.h>
#include <fcntl.h>

class CgiHandler {
	public:
		CgiHandler(const char *cgiExecutable, const char *filePath);
		~CgiHandler();
		void executeScript(const char *method, const char *queryString, const char *body);
		std::string executeCgi(const char *method, const char *queryString, const char *body);

	private:
		const char *cgiExecutable;
		const char *filePath;
		int pipefd[2];
		pid_t pid;
		static CgiHandler *instance;
		void setupPipe();
		void readOutput(std::string &output);
		static void handleAlarm(int sig);
		void clean();
};

#endif