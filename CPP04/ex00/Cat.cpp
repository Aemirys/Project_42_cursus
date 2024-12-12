/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:56:40 by emy               #+#    #+#             */
/*   Updated: 2024/12/02 15:33:17 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : Animal("Cat") {
	std::cout << "Cat constructed." << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other) {
	std::cout << "Cat: " << type << " is copied!" << std::endl;
}

Cat& Cat::operator=(const Cat& other) {
	std::cout << "Cat: " << type << " assigned!" << std::endl;
	if(this != &other) {
		Animal::operator=(other);
	}
	return *this;
}

Cat::~Cat() {
	std::cout << "Cat destroyed!" << std::endl;
}

void    Cat::makeSound() const {
	std::cout << type << " says: Meow Meow!" << std::endl;
}