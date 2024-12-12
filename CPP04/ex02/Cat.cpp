/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:56:40 by emy               #+#    #+#             */
/*   Updated: 2024/12/02 15:38:46 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

int Cat::count = 0;

Cat::Cat() : AAnimal("Cat") {
	this->brain = new Brain("Cat");
	std::cout << "Cat " << ++count <<  " constructed." << std::endl;
}

Cat::Cat(const Cat& other) : AAnimal(other) {
	this->brain = new Brain(*other.brain);
	std::cout << "Cat: " << type << " is copied!" << std::endl;
}

Cat& Cat::operator=(const Cat& other) {
	std::cout << "Cat: " << type << " assigned!" << std::endl;
	if(this != &other) {
		delete this->brain;
		this->brain = new Brain(*other.brain);
		AAnimal::operator=(other);
	}
	return *this;
}

Cat::~Cat() {
	delete brain;
	std::cout << "Cat destroyed!" << std::endl;
}

void    Cat::makeSound() const {
	std::cout << type << " says: Meow Meow!" << std::endl;
}

Brain* Cat::getBrain() const {
	return brain;
}