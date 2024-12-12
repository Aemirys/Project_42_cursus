/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scalar.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:50:56 by estosche          #+#    #+#             */
/*   Updated: 2024/12/12 15:12:56 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALAR_HPP
#define SCALAR_HPP

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <cmath>

class ScalarConverter {
	public:
		static void convert(const std::string& literal);
	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter& other);
		ScalarConverter& operator=(const ScalarConverter& other);
		~ScalarConverter();
		static void convertToChar(const std::string& literal);
		static void convertToInt(const std::string& literal);
		static void convertToFloat(const std::string& literal);
		static void convertToDouble(const std::string& literal);
	
};
#endif