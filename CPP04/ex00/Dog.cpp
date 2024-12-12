/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:17:43 by emy               #+#    #+#             */
/*   Updated: 2024/12/02 15:33:28 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : Animal("Dog") {
	std::cout << "Dog constructed." << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other) {
	std::cout << "Dog: " << type << " is copied!" << std::endl;
}

Dog& Dog::operator=(const Dog& other) {
	
	std::cout << "Dog: " << type << " assigned!" << std::endl;
	if(this != &other) {
		Animal::operator=(other);
	}
	return *this;
}

Dog::~Dog() {
	std::cout << "Dog destroyed!" << std::endl;
}

void    Dog::makeSound() const {
	std::cout << type << " says: Wouf Wouf!" << std::endl;
}