/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replace.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:28:22 by estosche          #+#    #+#             */
/*   Updated: 2024/10/30 15:43:29 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLACE_HPP
#define REPLACE_HPP

#include <iostream>
#include <string>
#include <fstream>

class Replace
{
    public:
        Replace(const std::string &filename, const std:: string &s1, const std::string &s2);
        bool replaceAndWrite();
    private:
        std::string filename;
        std::string s1;
        std::string s2;

        bool processLine(std::string &line, std::ofstream &outFile);
};

#endif