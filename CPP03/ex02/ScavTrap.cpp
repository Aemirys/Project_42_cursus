/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:27:42 by estosche          #+#    #+#             */
/*   Updated: 2024/11/26 16:55:56 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name) {

	hitPoints = 100;
	energyPoints = 50;
	attackDamage = 20;
	std::cout << "ScavTrap " << name << " is constructed!" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other){
	hitPoints = other.hitPoints;
    energyPoints = other.energyPoints;
    attackDamage = other.attackDamage;
	std::cout << "ClapTrap " << name << "is copied!" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
	std::cout << "ClapTrap " << name << " assigned!" << std::endl;
	if(this != &other) {
		ClapTrap::operator=(other);
        hitPoints = other.hitPoints;
        energyPoints = other.energyPoints;
        attackDamage = other.attackDamage;
	}
	return *this;
}

ScavTrap::~ScavTrap() {

	std::cout << "ScavTrap " << name << " is destroyed!" << std::endl;
}

void    ScavTrap::attack(const std::string& target) {

	if (energyPoints > 0 || hitPoints > 0) {
        std::cout << "ScavTrap " << name << " ferociously attacks " << target << ", causing " 
				<< attackDamage << " points of damage!" << std::endl;
        energyPoints--;
    } else {
        std::cout << "ScavTrap " << name << " is unable to attack (no energy or health)!" << std::endl;
    }
}

void	ScavTrap::guardGate() {

	 std::cout << "ScavTrap " << name << " is now in Gate keeper mode!" << std::endl;
}