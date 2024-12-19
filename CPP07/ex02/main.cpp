/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:07:47 by estosche          #+#    #+#             */
/*   Updated: 2024/12/16 13:37:25 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"
#include <cstdlib>
#include <ctime>


#define MAX_VAL 10

int main() {

	std::cout << color << "--- Test default init ---" << resetcolor << std::endl;
	Array<int> intArray;
	
	std::cout << color << "\n--- Test init size ---" << resetcolor << std::endl;
	Array<int> intArraySize(10);
	for (unsigned int i = 0; i < intArraySize.size(); i++) {
		std::cout << "intArraySize[" << i << "] = " << intArraySize[i] << std::endl;
	}
	
	std::cout << color << "\n--- Test copy ---" << resetcolor << std::endl;
	Array<int> intArrayCopy(intArraySize);
	for (unsigned int i = 0; i < intArrayCopy.size(); i++) {
		std::cout << "intArrayCopy[" << i << "] = " << intArrayCopy[i] << std::endl;
	}

	std::cout << color << "\n--- Test assignement ---" << resetcolor << std::endl;
	Array<int> intArrayAssigned;
	intArrayAssigned = intArraySize;

	for (unsigned int i = 0; i < intArraySize.size(); i++) {
		if (intArrayAssigned[i] != intArraySize[i]) {
			std::cerr << "Assignment failed at index " << i << std::endl;
		} else {
			std::cout << "intArrayAssigned[" << i << "] = " << intArrayAssigned[i] << std::endl;
		}
	}
	
	std::cout << color << "\n--- Test index out of limits ---" << resetcolor << std::endl;
	try {
		intArray[-1] = 10;
	} catch (const std::out_of_range& e) {
		std::cout << "Exception caught for negative index: " << e.what() << std::endl;
	}

	try {
		intArray[200] = 10;
	} catch (const std::out_of_range& e) {
		std::cout << "Exception caught for out-of-bounds index: " << e.what() << std::endl;
	}

	std::cout << color << "\n--- Test different type ---" << resetcolor << std::endl;
	Array<float> floatArray(10);
	for (unsigned int i = 0; i < floatArray.size(); i++) {
		std::cout << "floatArray[" << i << "] = " << floatArray[i] << std::endl;
	}

	std::cout << color << "\n--- Test destruction ---" << resetcolor << std::endl;
	return 0;
}