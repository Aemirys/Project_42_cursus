/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:05:37 by emy               #+#    #+#             */
/*   Updated: 2024/12/02 15:35:42 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() :type("Animal") {
	std::cout << "Animal constructed." << std::endl;
}

Animal::Animal(std::string type) : type(type) {
	std::cout << "Animal of type " << type << " is constructed!" << std::endl;
}

Animal::Animal(const Animal& other) {
	*this = other;
	std::cout << "Animal of type " << type << " is copied!" << std::endl;
	
}

Animal& Animal::operator=(const Animal& other) {
	if(this != &other) {
		type = other.type;
	}
	std::cout << "Animal of type " << type << " assigned!" << std::endl;
	return *this;
}

Animal::~Animal() {
	std::cout << "Animal destroyed!" << std::endl;
}

void   Animal::makeSound() const {
	std::cout << "Animal makes a generic sound." << std::endl;
}

std::string Animal::getType() const {
	std::cout << "Type of Animal: ";
	return type;
}