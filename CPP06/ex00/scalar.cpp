/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalar.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:50:15 by estosche          #+#    #+#             */
/*   Updated: 2024/12/11 10:26:33 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scalar.hpp"

ScalarConverter::ScalarConverter() {
	std::cout << "ScalarConverter constructed" << std::endl;
}

ScalarConverter::~ScalarConverter() {
	std::cout << " ScalarConverter destroyed" << std::endl;
}

ScalarConverter::ScalarConverter(const ScalarConverter& other){
	*this = other;
	std::cout << "ScalarConverter is copied" << std::endl;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
	(void)other;
	std::cout << "ScalarConvert assigned" << std::endl;
	return *this;	
}

void ScalarConverter::convert(const std::string& literal) {
	convertToChar(literal);
	convertToInt(literal);
	convertToFloat(literal);
	convertToDouble(literal);
}

void ScalarConverter::convertToChar(const std::string& literal) {
	try {
		std::cout << "char: ";
		if (literal.length() == 1 && !std::isdigit(literal[0])) {
			char value = literal[0];
		if (std::isprint(value)) {
			std::cout << "'" << value << "'" << std::endl;
		} else {
			std::cout << "Non displayable" << std::endl;
		}
		} else {
			double value = std::atof(literal.c_str());
			if (value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max() || std::isnan(value) || value != static_cast<int>(value)) {
				std::cout << "impossible" << std::endl;
			} else if (!std::isprint(static_cast<char>(value))) {
				std::cout << "Non displayable" << std::endl;
			} else {
				std::cout << "'" << static_cast<char>(value) << "'" << std::endl;
			}
		}
	}
	catch (...) {
		std::cout << "char: impossible" << std::endl;
	}
}

void ScalarConverter::convertToInt(const std::string& literal) {
	try {
		std::cout << "int : ";
		if (literal.length() == 1 && !std::isdigit(literal[0])) {
			std::cout << static_cast<int>(literal[0]) << std::endl;
			return;
		}
		double value = std::atof(literal.c_str());
		if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max() || std::isnan(value) || std::isinf(value)) {
			std::cout << "impossible" << std::endl;
		} else {
			std::cout << static_cast<int>(value) << std::endl;
		}
	} catch (...) {
		std::cout << "int: impossible" << std::endl;
	}
}

void ScalarConverter::convertToFloat(const std::string& literal) {
	try {
		if (literal.length() == 1 && !std::isdigit(literal[0])) {
			std::cout << "float: " << static_cast<int>(literal[0]) << ".0f" << std::endl;
			return;
		}
		if (literal == "-inf" || literal == "+inf" || literal == "nan") {
			std::cout << "float: " << literal << "f" << std::endl;
		} else {
			float value = std::atof(literal.c_str());

			if (literal.empty() || std::isnan(value)) {
				std::cout << "float: impossible" << std::endl;
			} else if (std::isinf(value)) {
				std::cout << "float: " << (value > 0 ? "+inff" : "-inff") << std::endl;
			} else {

				if (value == static_cast<int>(value)) {
					std::cout << "float: " << value << ".0f" << std::endl;
				} else {
					std::cout << "float: " << value << "f" << std::endl;
				}
			}
		}
	} catch (...) {
		std::cout << "float: impossible" << std::endl;
	}
}

void ScalarConverter::convertToDouble(const std::string& literal) {
	try {
		if (literal.length() == 1 && !std::isdigit(literal[0])) {
			std::cout << "double: " << static_cast<int>(literal[0]) << ".0" << std::endl;
			return;
		}
		if (literal == "-inf" || literal == "+inf" || literal == "nan") {
			std::cout << "double: " << literal << std::endl;
		}
		else {

			double value = std::atof(literal.c_str());

			if (literal.empty() || std::isnan(value)) {
				std::cout << "double: impossible" << std::endl;
			} else if (std::isinf(value)) {
				std::cout << "double: " << (value > 0 ? "+inf" : "-inf") << std::endl;
			} else {

				if (value == static_cast<int>(value)) {
					std::cout << "double: " << value << ".0" << std::endl;
				} else {
					std::cout << "double: " << value << std::endl;
				}
			}
		}
	} catch (...) {
		std::cout << "double: impossible" << std::endl;
	}
}