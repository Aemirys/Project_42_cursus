/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replace.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:32:41 by estosche          #+#    #+#             */
/*   Updated: 2024/10/30 16:32:01 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Replace.hpp"

Replace::Replace(const std::string &filename, const std::string &s1, const std::string &s2)
    : filename(filename), s1(s1), s2(s2) {}

bool Replace::replaceAndWrite() {
    std::ifstream inFile(filename.c_str());
    if (!inFile) {
        std::cerr << "Error: Couldn't open file " << filename << std::endl;
        return false;
    }

    std::ofstream outFile((filename + ".replace").c_str());
    if (!outFile) {
        std::cerr << "Error: Couldn't create output file " << filename + ".replace" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (!processLine(line, outFile)) {
            inFile.close();
            outFile.close();
            return false;
        }
        outFile << '\n';
    }
    inFile.close();
    outFile.close();
    return true;
}

bool Replace::processLine(std::string &line, std::ofstream &outFile) {
    size_t pos = 0;
    size_t found;

    while ((found = line.find(s1, pos)) != std::string::npos) {
        
        outFile << line.substr(pos, found - pos); 
        outFile << s2; 
        pos = found + s1.length(); 
    }
    outFile << line.substr(pos); 
    return true;
}
