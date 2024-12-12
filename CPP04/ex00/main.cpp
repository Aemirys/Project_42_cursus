/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:59:06 by emy               #+#    #+#             */
/*   Updated: 2024/12/02 16:27:18 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	std::cout << "\n--- Basic Polymorphism Tests ---\n";
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;

	i->makeSound(); 
	j->makeSound();
	meta->makeSound();

	delete meta;
	delete j;
	delete i;

	std::cout << "\n--- Copy and Assignment Tests ---\n";

	Dog originalDog;
	Dog copiedDog(originalDog);
	Dog assignedDog;
	assignedDog = originalDog;

	Cat originalCat;
	Cat copiedCat(originalCat);
	Cat assignedCat;
	assignedCat = originalCat;

	std::cout << "\n--- Dynamic Behavior Tests ---\n";

	Animal* animal = new Animal();
	Animal* dog = new Dog();
	Animal* cat = new Cat();

	animal->makeSound();
	dog->makeSound();
	cat->makeSound();

	delete animal;
	delete dog;
	delete cat;

	std::cout << "\n--- WrongAnimal Tests ---\n";

	const WrongAnimal* wrongMeta = new WrongAnimal();
	const WrongAnimal* wrongCat = new WrongCat();

	std::cout << "Type de wrongCat: " << wrongCat->getType() << std::endl;

	wrongCat->makeSound();
	//wrongMeta->makeSound();

	delete wrongMeta;
	delete wrongCat;

	std::cout << "\n---End of Tests ---\n";
	return 0;

}