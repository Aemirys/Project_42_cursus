/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:58:05 by estosche          #+#    #+#             */
/*   Updated: 2024/11/26 16:31:43 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap() {}

FragTrap::FragTrap(const std::string& name) : ClapTrap(name) {

	hitPoints = 100;
	energyPoints = 100;
	attackDamage = 30;
	std::cout << "FragTrap " << this->name << " is constructed!" << std::endl;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other){
	*this=other;
	std::cout << "FragTrap " << name << " is copied!" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap &other) {
	std::cout << "FragTrap " << this->name << " assigned!" << std::endl;
	if(this != &other) {
		ClapTrap::operator=(other);
        this->hitPoints = other.hitPoints;
		this->energyPoints = other.energyPoints;
		this->attackDamage = other.attackDamage;
	}
	return *this;
}

FragTrap::~FragTrap() {

	std::cout << "FragTrap " << this->name << " is destroyed!" << std::endl;
}

void FragTrap::highFivesGuys() {
	std::cout << "Fragtrap " << this->name << " says: High five, guys!" << std::endl;
}