/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:58:43 by estosche          #+#    #+#             */
/*   Updated: 2024/12/02 15:29:02 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria(std::string const &type) : type(type) {
	std::cout << "AMateria constructor called for " << type << std::endl;
}

AMateria::AMateria(AMateria const & other) : type(other.type) {
	std::cout << "AMateria copy constructor called for " << type << std::endl;
}

AMateria & AMateria::operator=(AMateria const & other) {
	if (this != &other) {
		std::cout << "AMateria assignment operator called for " << other.type << std::endl;
		type = other.type;
	}
	return *this;
}

AMateria::~AMateria(){
	std::cout << "AMateria destructor called for " << type << std::endl;
}

std::string const & AMateria::getType() const {
	return type;
}

void AMateria::use(ICharacter& target) {
	std::cout << "* uses AMateria on " << target.getName() << " *" << std::endl;
}