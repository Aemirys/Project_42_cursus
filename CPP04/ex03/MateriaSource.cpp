/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:41:17 by estosche          #+#    #+#             */
/*   Updated: 2024/12/02 15:28:31 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

MateriaSource::MateriaSource() {
	std::cout << "MateriaSource constructor called" << std::endl;
	for (int i = 0; i < 4; ++i)
		materia[i] = NULL;
}

MateriaSource::~MateriaSource() {
	std::cout << "MateriaSource destructor called" << std::endl;
	for (int i = 0; i < 4; ++i)
		delete materia[i];
}

MateriaSource::MateriaSource(MateriaSource const & other) {
	std::cout << "MateriaSource copy constructor called" << std::endl;
	for (int i = 0; i < 4; ++i) {
		if (other.materia[i])
			materia[i] = other.materia[i]->clone();
		else
			materia[i] = NULL;
	}
}

MateriaSource & MateriaSource::operator=(MateriaSource const & other) {
	if (this != &other) {
		std::cout << "MateriaSource assignment operator called" << std::endl;
		for (int i = 0; i < 4; ++i) {
			delete materia[i];
			if (other.materia[i])
				materia[i] = other.materia[i]->clone();
			else
				materia[i] = NULL;
		}
	}
	return *this;
}

void MateriaSource::learnMateria(AMateria* m) {
	for (int i = 0; i < 4; ++i) {
		if (!materia[i]) {
			materia[i] = m;
			std::cout << "Learned " << m->getType() << " materia" << std::endl;
			return;
		}
	}
	std::cout << "No room to learn new materia" << std::endl;
}

AMateria* MateriaSource::createMateria(std::string const & type) {
	for (int i = 0; i < 4; ++i) {
		if (materia[i] && materia[i]->getType() == type)
			return materia[i]->clone();
	}
	std::cout << "Materia " << type << " not found!" << std::endl;
	return NULL;
}