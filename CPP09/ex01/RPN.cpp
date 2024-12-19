/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:46:00 by estosche          #+#    #+#             */
/*   Updated: 2024/12/18 15:06:57 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

bool RPN::isOperator(const std::string& token) {
	return token == "+" || token == "-" || token == "*" || token == "/";
}

int RPN::applyOperator(const std::string& op, int a, int b) {
	if(op == "+")
		return a + b;
	if (op == "-")
		return a - b;
	if(op == "*")
		return a * b;
	if (op == "/") {
		if (b == 0)
			throw std::invalid_argument("Error");
		return a / b;
	}
	throw std::invalid_argument("Unknown operator");
}

int RPN::evaluateRPN(const std::string& expression) {
	std::stack<int> stack;
	std::stringstream ss(expression);
	std::string token;

	while (ss >> token) {
		if (isdigit(token[0]) && token.size() == 1) {
			stack.push(token[0] - '0');
		} else if (isOperator(token)) {
			if (stack.size() < 2)
				throw std::invalid_argument("Error");
			int b = stack.top();
			stack.pop();
			int a = stack.top();
			stack.pop();

			stack.push(applyOperator(token, a, b));
		} else {
			throw std::invalid_argument("Error");
		}
	}
	if (stack.size() != 1) throw std::invalid_argument("Error");
		return stack.top();
}