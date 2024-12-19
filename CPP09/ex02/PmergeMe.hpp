/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:01:18 by estosche          #+#    #+#             */
/*   Updated: 2024/12/19 13:04:25 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <string>
#include <sstream>
#include <stdexcept>
#include <ctime>

#define color "\033[1;3;38;5;125m"
#define resetcolor "\033[0m"

class PmergeMe {
	private:
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		
	public:
		PmergeMe();
		~PmergeMe();

		void validateInput(int argc, char** argv);
		bool isDigitsOnly(const std::string& str);
		std::vector<int> parseInputToVector(char** argv);
		std::deque<int> parseInputToDeque(char** argv);
		void mergeInsertSortVector(std::vector<int>& vec);
		void mergeInsertSortDeque(std::deque<int>& deq);
		void insertionSort(std::vector<int>& vec, size_t start, size_t end);
		void mergeInsertSort(std::vector<int>& vec, size_t start, size_t end);
		void run(int argc, char** argv);
};

#endif