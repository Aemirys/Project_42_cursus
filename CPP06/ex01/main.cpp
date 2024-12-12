/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:53:38 by estosche          #+#    #+#             */
/*   Updated: 2024/12/12 15:14:20 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int main() {

	Data myData;
	myData.id = 123;
	myData.name = "Test Data";

	std::cout << color << "=== Initial Data ===" << resetcolor << std::endl;
	std::cout << "Address of Data: " << &myData << std::endl;
	std::cout << "ID: " << myData.id << ", Name: " << myData.name << std::endl;

	uintptr_t raw = Serializer::serialize(&myData);
	std::cout << color << "\n=== Serialization ===" << resetcolor << std::endl;
	std::cout << "Serialized value (uintptr_t): " << raw << std::endl;

	Data* deserializedData = Serializer::deserialize(raw);
	std::cout << color << "\n=== Deserialization ===" << resetcolor << std::endl;
	std::cout << "Deserialized address: " << deserializedData << std::endl;

	std::cout << color << "\n=== Validation ===" << resetcolor << std::endl;
	if (deserializedData == &myData) {
		std::cout << "Test passed: Addresses match!" << std::endl;
	} else {
		std::cout << "Test failed: Addresses do not match." << std::endl;
	}

	std::cout << color << "\n=== Deserialized Data ===" << resetcolor << std::endl;
	std::cout << "ID: " << deserializedData->id << ", Name: " << deserializedData->name << std::endl;

	return 0;
}