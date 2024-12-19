/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:04:55 by estosche          #+#    #+#             */
/*   Updated: 2024/12/19 17:07:54 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

bool PmergeMe::isDigitsOnly(const std::string& str) {
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
		if (!std::isdigit(*it)) {
			return false;
		}
	}
	return true;
}

void PmergeMe::validateInput(int argc, char** argv) {
	if (argc < 2) {
		throw std::invalid_argument("Error: No input provided");
	}
	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if (arg.empty() || !isDigitsOnly(arg)) {
			throw std::invalid_argument("Error: Invalid input. Only positive integers are allowed.");
		}
	}
}

std::vector<int> PmergeMe::parseInputToVector(char** argv) {
	std::vector<int> vec;
	for (int i = 1; argv[i]; ++i) {
		vec.push_back(atoi(argv[i]));
	}
	return vec;
}

std::deque<int> PmergeMe::parseInputToDeque(char** argv) {
	std::deque<int> deq;
	for (int i = 1; argv[i]; ++i) {
		deq.push_back(atoi(argv[i]));
	}
	return deq;
}

void PmergeMe::mergeInsertSortVector(std::vector<int>& vec) {
	if (vec.size() <= 1)
		return;
	if(vec.size() < 16)
		std::sort(vec.begin(), vec.end());
	else {
		size_t mid = vec.size() / 2;
		std::vector<int> left(vec.begin(), vec.begin() + mid);
		std::vector<int> right(vec.begin() + mid, vec.end());

		mergeInsertSortVector(left);
		mergeInsertSortVector(right);

		std::merge(left.begin(), left.end(), right.begin(), right.end(), vec.begin());
	}
}
	

void PmergeMe::mergeInsertSortDeque(std::deque<int>& deq) {
	if (deq.size() <= 1) return;
	if(deq.size() < 16)
		std::sort(deq.begin(), deq.end());
	else {
		size_t mid = deq.size() / 2;
		std::deque<int> left(deq.begin(), deq.begin() + mid);
		std::deque<int> right(deq.begin() + mid, deq.end());

		mergeInsertSortDeque(left);
		mergeInsertSortDeque(right);

		std::merge(left.begin(), left.end(), right.begin(), right.end(), deq.begin());
	}
	
}

void PmergeMe::run(int argc, char** argv) {
	try {
		validateInput(argc, argv);

		std::vector<int> vec = parseInputToVector(argv);
		std::deque<int> deq = parseInputToDeque(argv);

		std::cout << color << "Before: " << resetcolor;
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		clock_t startVec = clock();
		mergeInsertSortVector(vec);
		clock_t endVec = clock();
		double durationVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1e6;

		clock_t startDeq = clock();
		mergeInsertSortDeque(deq);
		clock_t endDeq = clock();
		double durationDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1e6;

		std::cout << color << "After: " << resetcolor;
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::cout << "Time to process a range of " << vec.size()
				  << " elements with std::vector: " << color << durationVec << " us" << resetcolor << std::endl;
		std::cout << "Time to process a range of " << deq.size()
				  << " elements with std::deque: " << color << durationDeq << " us" << resetcolor << std::endl;
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}