/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:41:31 by estosche          #+#    #+#             */
/*   Updated: 2024/11/27 16:12:51 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap() {}

ClapTrap:: ClapTrap(std::string name) : name(name), hitPoints(10), energyPoints(10), attackDamage(0) {
	
	std::cout << "ClapTrap " << name << " is constructed!" << std::endl;
}

ClapTrap:: ~ClapTrap() {
	
	std::cout << "ClapTrap " << name << " is destroyed" << std::endl;
}

void ClapTrap:: life() {

	std::cout << name << " has " << hitPoints << " Hit points and " << energyPoints << " Energy Points." << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other) {

	std::cout << "ClapTrap " << name << "copy constructed!" << std::endl;
	*this = other;
}

ClapTrap& ClapTrap::operator=(const ClapTrap &other) {
	
	if(this != &other) {
	 	name = other.name;
		hitPoints = other.hitPoints;
		energyPoints = other.energyPoints;
		attackDamage = other.attackDamage;
	}
	std::cout << "ClapTrap " << name << " assigned!" << std::endl;
	return *this;
}

void ClapTrap:: attack(const std::string& target) {
	
	if(hitPoints > 0 && energyPoints > 0){
		energyPoints -= 1;
		std::cout << "ClapeTrap " << name << " attacks " << target << ", causing " << attackDamage << " points of damage!" << std::endl;
	} else {
		std::cout << "ClapTrap " << name << "can't attack! Not enough energy or hit points!" << std::endl;
	}
	
}

void ClapTrap:: takeDamage(unsigned int amount) {
	
	if(hitPoints > 0) {
		
		hitPoints -= amount;
		std::cout << "ClapTrap " << name << " takes " << amount << " points of damage!" << std::endl;
		if(hitPoints <= 0){
			hitPoints = 0;
			std::cout << "Claptrap " << name << " is out of hit points!" << std::endl;
		}
	}
}

void ClapTrap:: beRepaired(unsigned int amount) {

	if(hitPoints > 0 && energyPoints > 0) {
		
		energyPoints-= 1;
		hitPoints += amount;
		std::cout << "ClapTrap " << name << " repairs itself, recovering " << amount << " hit points!" << std::endl;
	} else {
		
		std::cout << "Claptrap " << name << " can't repair itself! Not enough energy or hit points!" << std::endl;
	}
}

