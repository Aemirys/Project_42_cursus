/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:08:57 by estosche          #+#    #+#             */
/*   Updated: 2024/10/30 12:43:38 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie() : name(""), number(0){}

Zombie:: Zombie(std::string name, int number) : name(name), number(number) {
    std::cout << name << number << " is created" << std::endl;
}

Zombie::~Zombie(){
    std::cout << name << " " << number << " is destroyed" << std::endl;
}

void Zombie::announce() const {
    std::cout << name << " " << number << ":  BraiiiiiiinnnzzzZ..." << std::endl;
}