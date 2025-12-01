/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:59:19 by estosche          #+#    #+#             */
/*   Updated: 2025/03/11 11:22:26 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <vector>
#include <string>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <locale>
#include <string>
#include <cctype>
#include <cstdlib>


class LocationConfig {
	public:
		std::string path;
		std::string root;
		std::string index;
		std::string cgi_pass;
		std::vector<std::string> allowed_methods;
		std::string redirect_url;
		int client_max_body_size;

		std::vector<std::string> allow_ips;
		bool deny_all;
		bool autoindex;
		LocationConfig() : client_max_body_size(-1), deny_all(false), autoindex(false) {}
		~LocationConfig() {}
};

class ServerConfig {
	public:
		std::vector<int> ports;
		std::string server_name;
		std::string root;
		std::string index;
		std::string cgi_pass;
		int client_max_body_size;

		std::map<int, std::string> error_pages;
		std::vector<LocationConfig> locations;
		std::vector<std::string> allowed_methods;
		ServerConfig() : client_max_body_size(-1) {}
		~ServerConfig() {}
};

class Config {
	private:
		std::vector<ServerConfig> servers;
	public:
		Config();
		~Config();
		std::vector<int> getPorts() const;
		std::string getRoot() const;
		std::string getAdmin() const;
		std::vector<ServerConfig> getServers() const;
		std::string getCgiPass(const std::string& locationPath) const;
		std::string getIndex(const std::string& locationPath) const;
		bool loadConfig(const std::string& filename);
		void parseLine(const std::string& line, ServerConfig& server, LocationConfig* location);
		std::map<int, std::string> getErrorPages() const;
		std::set<std::string> getAllowedMethods(const std::string& path) const;
};


#endif