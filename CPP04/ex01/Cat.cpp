/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:56:40 by emy               #+#    #+#             */
/*   Updated: 2024/12/02 16:04:42 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

int Cat::Catcount = 0;

Cat::Cat() : Animal("Cat") {
	this->brain = new Brain("Cat");
	std::cout << "Cat " << Catcount++ <<  " constructed." << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other) {
	this->brain = new Brain(*other.brain);
	std::cout << "Cat: " << type << " is copied!" << std::endl;
}

Cat& Cat::operator=(const Cat& other) {
	std::cout << "Cat: " << type << " assigned!" << std::endl;
	if(this != &other) {
		delete this->brain;  // On supprime l'ancien brain
		this->brain = new Brain(*other.brain);
		Animal::operator=(other);
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