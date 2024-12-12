/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:22:56 by estosche          #+#    #+#             */
/*   Updated: 2024/12/02 15:27:51 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"
#include "IMateriaSource.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main() {

	std::cout << "\n--- Creation Materia Source---\n" << std::endl;
	IMateriaSource* materiaSource = new MateriaSource();
	materiaSource->learnMateria(new Ice());
	materiaSource->learnMateria(new Cure());
	
	std::cout << "\n--- Creation Players and Enemys ---\n" << std::endl;
	ICharacter* player = new Character("Player");
	ICharacter* enemy = new Character("Enemy");
	
	std::cout << "\n--- Creation Materias ---\n" << std::endl;
	AMateria* iceMateria = materiaSource->createMateria("ice");
	std::cout << "Created materia: " << iceMateria->getType() << "." << std::endl;
	AMateria* cureMateria = materiaSource->createMateria("cure");
	std::cout << "Created materia: " << cureMateria->getType() << "." << std::endl;
	
	std::cout << "\n--- Add materia to inventory ---\n" << std::endl;
	player->equip(iceMateria);
	player->equip(cureMateria);
	
	std::cout << "\n--- Player uses materias on Enemy ---\n" << std::endl;
	player->use(0, *enemy);
	player->use(1, *enemy);
	
	std::cout << "\n--- Player uses an empty inventory slot ---\n" << std::endl;
	player->use(2, *enemy);
	
	std::cout << "\n--- Player unequips Ice and Cure ---\n" << std::endl;
	player->unequip(0);
	player->unequip(1);
	
	std::cout << "\n--- Tests after unequips ---\n" << std::endl;
	player->use(0, *enemy);
	player->use(1, *enemy);
	
	std::cout << "\n--- Destroyed ---\n" << std::endl;
	delete materiaSource;
	delete player;
	delete enemy;
	
	std::cout << "\n--- Destroying manually unequipped materia: Ice.---\n" << std::endl;
	delete iceMateria;
	delete cureMateria;
	
	return 0;
}