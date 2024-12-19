/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:54:38 by estosche          #+#    #+#             */
/*   Updated: 2024/12/18 16:58:50 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

void testSubjectSpan() {
	std::cout << color << "===== Testing subject test =====\n" << resetcolor;

	Span sp = Span(5);

	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
}

void testInvalidCases() {
	std::cout << color << "\n===== Testing invalid cases =====\n" << resetcolor;
	std::cout << test << "\n===== Testing Span full =====\n" << resetest;
	Span sp(5);
	try {
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		sp.addNumber(100);
	} catch (const std::out_of_range &e) {
		std::cout << "Error: " << e.what() << "\n";
	}
	std::cout << test << "\n===== Testing Span empty =====\n" << resetest;
	Span emptySpan(0);
	try {
		emptySpan.shortestSpan();
	} catch (const std::logic_error &e) {
		std::cout << "Error: " << e.what() << "\n";
	}
	try {
		emptySpan.longestSpan();
	} catch (const std::logic_error &e) {
		std::cout << "Error: " << e.what() << "\n";
	}
	std::cout << test << "\n===== Testing Span single =====\n" << resetest;
	Span singleElementSpan(1);
	singleElementSpan.addNumber(100);
	try {
		singleElementSpan.shortestSpan();
	} catch (const std::logic_error &e) {
		std::cout << "Error: " << e.what() << "\n";
	}
	try {
		singleElementSpan.longestSpan();
	} catch (const std::logic_error &e) {
		std::cout << "Error: " << e.what() << "\n";
	}
	std::cout << std::endl;
}

void testAddRange() {
	std::cout << color << "\n===== Testing addRange with invalid inputs =====\n" << resetcolor;
	std::cout << test << "\n===== Testing Span =====\n" << resetest;
	Span sp(10);

	std::vector<int> largeRange;
	for (int i = 0; i < 10; ++i) {
		largeRange.push_back(100 + i);
	}
	try {
		sp.addRange(largeRange.begin(), largeRange.end());
	} catch (const std::logic_error &e) {
		std::cout << "Error: " << e.what() << "\n";
	}
	std::cout << "After adding range:\n";
	std::cout << "Shortest Span: " << sp.shortestSpan() << "\n";
	std::cout << "Longest Span: " << sp.longestSpan() << "\n";

	std::cout << test << "\n===== Testing span full =====\n" << resetest;
	std::vector<int> fullNumbers;

	fullNumbers.push_back(-5);
   	fullNumbers.push_back(-10);
	fullNumbers.push_back(-15);

	try {
		sp.addRange(fullNumbers.begin(), fullNumbers.end());
	} catch (const std::logic_error &e) {
		std::cout << "Error: " << e.what() << "\n";
	}
	std::cout << test << "\n===== Testing negative =====\n" << resetest;
	Span spa(3);
	std::vector<int> negativeNumbers;

	negativeNumbers.push_back(-5);
	negativeNumbers.push_back(-10);
	negativeNumbers.push_back(-15);

	try {
		spa.addRange(negativeNumbers.begin(), negativeNumbers.end());
	} catch (const std::logic_error &e) {
		std::cout << "Error: " << e.what() << "\n";
	}

	std::cout << "After adding range:\n";
	std::cout << "Shortest Span: " << spa.shortestSpan() << "\n";
	std::cout << "Longest Span: " << spa.longestSpan() << "\n";
	std::cout << std::endl;
}

int main() {
	testSubjectSpan();
	testInvalidCases();
	testAddRange();
	return 0;
}
