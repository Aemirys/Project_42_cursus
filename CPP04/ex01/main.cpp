/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:59:06 by emy               #+#    #+#             */
/*   Updated: 2024/12/02 15:41:54 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main() {
	
	const int arraySize = 4;
	Animal* animals[arraySize];

	std::cout << "=== Creating Dog and Cat Objects ===" << std::endl;
	for (int i = 0; i < arraySize; i++) {
		if (i % 2 == 0) {
			animals[i] = new Dog();
		} else {
			animals[i] = new Cat();
		}
	}

	std::cout << "\n=== Type and Sound Tests ===" << std::endl;

	for (int i = 0; i < arraySize; i++) {
		std::cout << "Animal at index " << i << ": ";
		std::cout << "Type: " << animals[i]->getType() << ", Sound: ";
		animals[i]->makeSound();
	}

	std::cout << "\n=== Adding Ideas to Animals ===" << std::endl;
	Dog dog;
	Cat cat;

	dog.getBrain()->setIdea(0, "I want to fetch the ball.");
	dog.getBrain()->setIdea(1, "I love bones.");
	
	cat.getBrain()->setIdea(0, "I want to catch mice.");
	cat.getBrain()->setIdea(1, "I love to sleep in the sun.");

	std::cout << "\n=== Displaying Dog's Ideas ===" << std::endl;
	std::cout << "Dog's Idea 0: " << dog.getBrain()->getIdea(0) << std::endl;
	std::cout << "Dog's Idea 1: " << dog.getBrain()->getIdea(1) << std::endl;

	std::cout << "\n=== Displaying Cat's Ideas ===" << std::endl;
	std::cout << "Cat's Idea 0: " << cat.getBrain()->getIdea(0) << std::endl;
	std::cout << "Cat's Idea 1: " << cat.getBrain()->getIdea(1) << std::endl;

	std::cout << "\n=== Assignment Tests ===" << std::endl;

	Dog dog1;
	Cat cat1;

	Dog dog2;
	Cat cat2;

	dog2 = dog1;
	cat2 = cat1;

	std::cout << "After assignment, dog2: " << dog2.getType() << ", that makes: ";
	dog2.makeSound();
	std::cout << "After assignment, cat2: " << cat2.getType() << ", that makes: ";
	cat2.makeSound();

	std::cout << "\n=== Deleting Animals ===" << std::endl;
	for (int i = 0; i < arraySize; i++) {
		delete animals[i];
	}

	return 0;
}