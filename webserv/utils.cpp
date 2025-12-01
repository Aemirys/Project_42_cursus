/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:45:00 by estosche          #+#    #+#             */
/*   Updated: 2025/03/04 11:03:04 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

std::string readFile(const std::string &filePath) {
	std::ifstream file(filePath.c_str());
	if (!file) return "";

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

std::string intToString(int value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}