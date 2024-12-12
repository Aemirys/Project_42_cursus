/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:18:49 by estosche          #+#    #+#             */
/*   Updated: 2024/12/02 15:29:08 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character(std::string const & name) : name(name) {
	std::cout << "Character constructor called for " << name << std::endl;
	for (int i = 0; i < 4; ++i)
		inventory[i] = NULL;
}

Character::Character(Character const & other) : name(other.name) {
	std::cout << "Character copy constructor called for " << name << std::endl;
	for (int i = 0; i < 4; ++i) {
		if (other.inventory[i])
			inventory[i] = other.inventory[i]->clone();
		else
			inventory[i] = NULL;
	}
}

Character & Character::operator=(Character const & other) {
	if (this != &other) {
		std::cout << "Character assignment operator called for " << other.name << std::endl;
		name = other.name;
		for (int i = 0; i < 4; ++i) {
			delete inventory[i];
			if (other.inventory[i])
				inventory[i] = other.inventory[i]->clone();
			else
				inventory[i] = NULL;
		}
	}
	return *this;
}

Character::~Character() {
	std::cout << "Character destructor called for " << name << std::endl;
	for (int i = 0; i < 4; ++i)
		delete inventory[i];
}

const std::string& Character::getName() const {
	return name;
}

void Character::equip(AMateria* m) {
	for (int i = 0; i < 4; ++i) {
		if (!inventory[i]) {
			inventory[i] = m;
			std::cout << "Equipped " << m->getType() << " to inventory slot " << i << std::endl;
			return;
		}
	}
	std::cout << "No available slot to equip " << m->getType() << std::endl;
}

void Character::unequip(int idx) {
	if (idx >= 0 && idx < 4 && inventory[idx]) {
		std::cout << "Unequipped " << inventory[idx]->getType() << " from slot " << idx << std::endl;
		inventory[idx] = NULL;
	}
}

void Character::use(int idx, ICharacter& target) {
	if (idx < 0 || idx >= 4) {
		std::cout << "Invalid inventory slot: " << idx << "." << std::endl;
		return;
	}
	if (!inventory[idx]) {
		std::cout << "Inventory slot " << idx << " is empty." << std::endl;
		return;
	}
	std::cout << "Using " << inventory[idx]->getType() << " on " << target.getName() << "." << std::endl;
	inventory[idx]->use(target);
}