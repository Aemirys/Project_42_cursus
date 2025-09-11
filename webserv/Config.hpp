/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:59:19 by estosche          #+#    #+#             */
/*   Updated: 2025/02/05 15:09:27 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <vector>
#include <string>

class Config{
  public:
        Config();
        bool loadConfig(const std::string& filename);
        void parseLine(const std::string& line);
        int getPort() const;
        std::vector<int> getPorts(int& num_ports);
        std::string getRoot() const;
        std::string getErrorPage403() const;
        std::string getErrorPage404() const;
        std::string getErrorPage405() const;
        std::string getErrorPage500() const;
        std::string getErrorPage503() const;
        std::string getAdmin() const;
        std::vector<std::string> getAllowedMethods() const;
    private:
        std::vector<int> ports;
        std::string root;
        std::string error_page_403;
        std::string error_page_404;
        std::string error_page_405;
        std::string error_page_500;
        std::string error_page_503;
        std::string admin;
        std::vector<std::string> allowed_methods;
        
};
#endif