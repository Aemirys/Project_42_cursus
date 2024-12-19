/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:24:09 by estosche          #+#    #+#             */
/*   Updated: 2024/12/16 13:38:36 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

void printInt(const int& x) {
	std::cout << x << " ";
}

void doubleValue(int& x) {
	x *= 2;
}

template <typename T>
void printElement(const T& elem) {
	std::cout << elem << " ";
}

int main() {
	std::cout << std::endl;
	int intArray[] = {1, 2, 3, 4, 5};
	size_t intArraySize = sizeof(intArray) / sizeof(intArray[0]);

	std::cout << color << "Array before doubling: " << resetcolor;
	iter(intArray, intArraySize, printInt);
	std::cout << std::endl;

	iter(intArray, intArraySize, doubleValue);

	std::cout << color << "Array after doubling: " << resetcolor;
	iter(intArray, intArraySize, printInt);
	std::cout << std::endl;

	std::string strArray[] = {"Hello", "World", "Templates", "C++"};
	size_t strArraySize = sizeof(strArray) / sizeof(strArray[0]);

	std::cout << color << "String array: " << resetcolor;
	iter(strArray, strArraySize, printElement<std::string>);
	std::cout << std::endl;

	return 0;
}