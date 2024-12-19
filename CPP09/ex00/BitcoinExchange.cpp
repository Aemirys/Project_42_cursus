/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:57:10 by estosche          #+#    #+#             */
/*   Updated: 2024/12/19 13:21:57 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string& priceFile) {
	 loadDataCSV(priceFile);
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDataCSV(const std::string& priceFile) {
	std::ifstream file(priceFile.c_str());
	if (!file.is_open()) {
		throw std::runtime_error("Error: could not open price data file.");
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream ss(line);
		std::string date;
		float rate;
		std::getline(ss, date, ',');
		ss >> rate;

		priceData[date] = rate;
	}
}

bool BitcoinExchange::isValidDate(const std::string& date) {
	if (date.length() != 10) return false;
	if (date[4] != '-' || date[7] != '-') return false;
	for (size_t i = 0; i < 10; ++i) {
		if ((i == 4 || i == 7) && date[i] == '-') continue;
		if (!isdigit(date[i])) return false;
	}
	return true;
}

bool BitcoinExchange::isValidValue(const std::string& value) {
	char* end;
	double val = std::strtod(value.c_str(), &end);

	if (val < 0) {
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}

	if (val > 1000) {
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}

	return true;
}

std::string BitcoinExchange::findClosestDate(const std::string& inputDate) {
	std::map<std::string, float>::const_iterator it = priceData.lower_bound(inputDate);
	if (it == priceData.begin()) return it->first;
	if (it == priceData.end()) {
		--it;
		return it->first;
	}

	std::map<std::string, float>::const_iterator prevIt = it;
	--prevIt;

	if (inputDate < it->first) {
		return prevIt->first;
	} else {
		return it->first;
	}
}

void BitcoinExchange::processFile(const std::string& inputFile) {
	std::ifstream file(inputFile.c_str());
	if (!file) {
		throw std::runtime_error("Error: could not open file.");
	}

	std::string line;
	bool isFirstLine = true;

	while (std::getline(file, line)) {
		if (isFirstLine) {
			isFirstLine = false;
			continue;
		}

		std::istringstream ss(line);
		std::string date, value;

		if (!std::getline(ss, date, '|') || !std::getline(ss, value)) {
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		date.erase(0, date.find_first_not_of(" \t"));
		date.erase(date.find_last_not_of(" \t") + 1);
		value.erase(0, value.find_first_not_of(" \t"));
		value.erase(value.find_last_not_of(" \t") + 1);

		if (!isValidDate(date)) {
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		if (!isValidValue(value)) {
			continue;
		}

		std::string closestDate = findClosestDate(date);
		float rate = priceData[closestDate];
		float result = std::atof(value.c_str()) * rate;

		std::cout << date << " => " << value << " = " << result << std::endl;
	}
}