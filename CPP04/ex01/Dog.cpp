/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:17:43 by emy               #+#    #+#             */
/*   Updated: 2024/12/02 16:02:12 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

int Dog::dogCount = 0;

Dog::Dog() : Animal("Dog") {
	this->brain = new Brain("Dog");
	std::cout << "Dog " << dogCount++ <<  " constructed." << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other) {
	this->brain = new Brain(*other.brain);
	std::cout << "Dog: " << type << " is copied!" << std::endl;
}

Dog& Dog::operator=(const Dog& other) {
	std::cout << "Dog: " << type << " assigned!" << std::endl;
	if(this != &other) {
		delete this->brain;
		this->brain = new Brain(*other.brain);
		Animal::operator=(other);
	}
	return *this;
}

Dog::~Dog() {
	delete brain;
	std::cout << "Dog destroyed!" << std::endl;
}

void    Dog::makeSound() const {
	std::cout << type << " says: Wouf Wouf!" << std::endl;
}

Brain* Dog::getBrain() const {
	return brain;
}