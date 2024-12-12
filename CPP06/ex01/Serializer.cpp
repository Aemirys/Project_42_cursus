/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:50:12 by estosche          #+#    #+#             */
/*   Updated: 2024/12/12 10:16:13 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

Serializer::Serializer() {
	std::cout << "Serializer constructed" << std::endl;
}

Serializer::Serializer(const Serializer& other) {
	*this = other;
	std::cout << "Serializer is copied" << std::endl;
}

Serializer& Serializer::operator=(const Serializer& other) {
	(void)other;
	std::cout << "Serializer assigned" << std::endl;
	return *this;	
}

Serializer::~Serializer() {
	 std::cout << "Serializer destroyed" << std::endl;
}

uintptr_t Serializer::serialize(Data* ptr) {
	return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw) {
	return reinterpret_cast<Data*>(raw);
}