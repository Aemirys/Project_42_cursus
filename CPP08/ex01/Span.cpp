/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:38:39 by estosche          #+#    #+#             */
/*   Updated: 2024/12/18 16:08:40 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(unsigned int maxSize) : _maxSize(maxSize) {
	std::cout << "Default constructed." << std::endl;
}

Span::Span(const Span& other) : _maxSize(other._maxSize), _numbers(other._numbers) {
	std::cout << "Span copied." << std::endl;
}

Span& Span::operator=(const Span& other) {
	std::cout << "Span assigned" << std::endl;
	if(this != &other) {
		_maxSize = other._maxSize;
		_numbers = other._numbers;
	}
	return *this;
}

Span::~Span() {
	std::cout << "Span destroyed" << std::endl;
}

void Span::addNumber(int number) {
	if(_numbers.size() >= _maxSize) {
		throw std::out_of_range("Span is already full");
	}
	_numbers.push_back(number);
}

void Span::addRange(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
	while(begin != end) {
		addNumber(*begin);
		++begin;
	}
}

int Span::shortestSpan() const {
	if(_numbers.size() < 2) {
		throw std::logic_error("Not enough numbers to calculate span");
	}
	std::vector<int> sortedNumbers = _numbers;
	std::sort(sortedNumbers.begin(), sortedNumbers.end());
	int minSpan = sortedNumbers[1] - sortedNumbers[0];
	for(size_t i = 1; i < sortedNumbers.size() - 1; i++) {
		int span = sortedNumbers[i + 1] - sortedNumbers[i];
		if (span < minSpan) {
			minSpan = span;
		}
	}
	return minSpan;
}

int Span::longestSpan() const {
	if(_numbers.size() < 2) {
		throw std::logic_error("Not enough numbers to calculate span");
	}
	int minNumber = *std::min_element(_numbers.begin(), _numbers.end());
	int maxNumber = *std::max_element(_numbers.begin(), _numbers.end());
	return maxNumber - minNumber;
}