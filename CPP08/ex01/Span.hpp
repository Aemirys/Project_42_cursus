/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:33:19 by estosche          #+#    #+#             */
/*   Updated: 2024/12/18 16:34:07 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>

#define color "\033[1;3;38;5;125m"
#define resetcolor "\033[0m"

#define test "\033[1;3;38;5;140m"
#define resetest "\033[0m"
class Span
{
	private:
		unsigned int _maxSize;
		std::vector<int>_numbers;
	public:
		Span(unsigned int maxSize);
		Span(const Span& other);
		Span& operator=(const Span& other);
		~Span();
		void addNumber(int number);

		void addRange(std::vector<int>::iterator begin, std::vector<int>::iterator end);

		int shortestSpan() const;
		int longestSpan() const;
		
};

#endif