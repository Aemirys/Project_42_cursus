/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:06:55 by estosche          #+#    #+#             */
/*   Updated: 2024/10/30 14:37:16 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(const std::string& name) : name(name), weapon(NULL){}

void HumanB::setWeapon(Weapon& newWeapon){
    weapon = &newWeapon;
}

void HumanB::attack() const {
    if (weapon)
        std::cout << name << " attacks with " << weapon->getType() << std::endl;
    else
        std::cout << name << " has no weapon to attack!" << std::endl;
}