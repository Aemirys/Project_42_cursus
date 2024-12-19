/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:35:36 by estosche          #+#    #+#             */
/*   Updated: 2024/12/18 15:05:28 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cctype>

class RPN
{
	private:
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		bool isOperator(const std::string& token);
		int applyOperator(const std::string& op, int a, int b);

	public:
		RPN();
		~RPN();
		int evaluateRPN(const std::string& expression);
};

#endif