/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:05:37 by emy               #+#    #+#             */
/*   Updated: 2024/12/02 15:42:08 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

AAnimal::AAnimal() :type("Animal") {
	std::cout << "Animal constructed." << std::endl;
}

AAnimal::AAnimal(std::string type) : type(type) {
	std::cout << "Animal of type " << type << " is constructed!" << std::endl;
}

AAnimal::AAnimal(const AAnimal& other) {
	*this = other;
	std::cout << "Animal of type " << type << " is copied!" << std::endl;
	
}

AAnimal& AAnimal::operator=(const AAnimal& other) {	
	if(this != &other) {
		type = other.type;
	}
	std::cout << "Animal of type " << type << " assigned!" << std::endl;
	return *this;
}

AAnimal::~AAnimal() {	
	std::cout << "Animal destroyed!" << std::endl;
}

void  AAnimal::makeSound() const {
	std::cout << "Animal makes a generic sound." << std::endl;
}

std::string AAnimal::getType() const {
	std::cout << "Type of Animal: ";
	return type;
}