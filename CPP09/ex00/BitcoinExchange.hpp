/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:57:26 by estosche          #+#    #+#             */
/*   Updated: 2024/12/18 14:57:05 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>

class BitcoinExchange
{
	private:
		std::map<std::string, float> priceData;
		std::string filename;
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
	public:
		BitcoinExchange(const std::string& priceFile);
		~BitcoinExchange();
		void loadDataCSV(const std::string& priceFile);
		bool isValidDate(const std::string& date);
		bool isValidValue(const std::string& value);
		std::string findClosestDate(const std::string& inputDate);
		void processFile(const std::string& inputFile);
};

#endif