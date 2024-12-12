/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:25:48 by emy               #+#    #+#             */
/*   Updated: 2024/12/02 15:38:26 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain(const std::string& type) : type(type) {
	std::cout << "Brain (" << type << ") constructed" << std::endl;
}

Brain::Brain(const Brain& other) {
	std::cout << "Brain (" << other.type << ") copied" << std::endl;
	//*this = other;
	type = other.type;
}

Brain& Brain::operator=(const Brain& other) {
	if (this != &other) {
		for (int i = 0; i < 100; i++) {
			ideas[i] = other.ideas[i];
		}
	}
	return *this;
}

Brain::~Brain() {
	
	std::cout << "Brain (" << type << ") destroyed." << std::endl;
}

void Brain::setIdea(int index, const std::string& idea) {
	if (index >= 0 && index < 100) {
		ideas[index] = idea;
	}
}

std::string Brain::getIdea(int index) const {
	if (index >= 0 && index < 100) {
		return ideas[index];
	}
	return "";
}

std::string Brain::getType() const {
	return type;
}