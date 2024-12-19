/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:54:23 by estosche          #+#    #+#             */
/*   Updated: 2024/12/19 13:16:28 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Error: Invalid input" << std::endl;
		return 1;
	}

	try {
		RPN rpnCalculator;
		std::string expression = argv[1];
		int result = rpnCalculator.evaluateRPN(expression);
		std::cout << result << std::endl;
	} catch (const std::invalid_argument& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}