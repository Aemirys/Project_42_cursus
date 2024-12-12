/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:07:07 by estosche          #+#    #+#             */
/*   Updated: 2024/10/30 14:23:01 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon() : type(""){}

Weapon::Weapon(const std::string& type) : type(type) {}
const std::string& Weapon::getType() const {
    return type;
}

void Weapon::setType(const std::string& newType){
    type = newType;
}

