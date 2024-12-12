/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:12:54 by estosche          #+#    #+#             */
/*   Updated: 2024/11/25 11:01:38 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed:: Fixed() : _num() {
	std::cout << "Default constructeur called" << std::endl;
}

Fixed:: Fixed(int intValue) {
	std::cout << "Int constructeur called" << std::endl;
	setRawBits(intValue << _nbr);
}

Fixed:: Fixed(float floatValue) {
	std::cout << "Float constructeur called" << std::endl;
	 setRawBits((int)(roundf(floatValue * (1 << _nbr))));
}
Fixed:: Fixed(const Fixed &other) : _num(other._num) {
	std::cout << "Copy constructeur called" << std::endl;
	*this = other;
}

Fixed& Fixed::operator=(const Fixed &other) {
	std::cout << "Copy assignement operator called" << std::endl;
	setRawBits(other.getRawBits());
	return *this;
}

Fixed::~Fixed() {
	std::cout << "Desructor called" << std::endl;
}

int Fixed::getRawBits(void) const {
	return _num;
}

void Fixed::setRawBits(int const raw) {
    _num = raw;
}

float Fixed::toFloat(void) const {
	return ((float)_num) / (1 << _nbr);
}

int Fixed::toInt(void) const {
	return _num >> _nbr;
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed) {
	os << fixed.toFloat();
	return os;
}