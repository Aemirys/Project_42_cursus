/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:15:41 by estosche          #+#    #+#             */
/*   Updated: 2024/11/25 12:49:51 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed:: Fixed() : num() {
	//std::cout << "Fixed Default constructor called" << std::endl;
}

Fixed:: Fixed(const float floatValue) : num(int(roundf(floatValue * (1 << _nbr)))) {
	//std::cout << "Fixed Float constructeur called" << std::endl;
}

Fixed:: Fixed(const int intValue) : num(intValue << _nbr) {
	//std::cout << "Fixed Int constructeur called" << std::endl;
}

Fixed:: Fixed(const Fixed &other) : num(other.num) {
	//std::cout << "Fixed Copy constructeur called" << std::endl;
}

Fixed::~Fixed() {
	//std::cout << "Fixed Desructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& other) {
	//std::cout << "Fixed Copy assignement operator called" << std::endl;
	if(this != &other) 
		setRawBits(other.getRawBits());
	return *this;
}

int Fixed::getRawBits(void) const {

    return num;
}

void Fixed::setRawBits(int const raw) {
    num = raw;
}

bool Fixed::operator>(const Fixed& other) const { return num > other.num;}
bool Fixed::operator<(const Fixed& other) const { return num < other.num;}
bool Fixed::operator>=(const Fixed& other) const { return num >= other.num;}
bool Fixed::operator<=(const Fixed& other) const { return num <= other.num;}
bool Fixed::operator==(const Fixed& other) const { return num == other.num;}
bool Fixed::operator!=(const Fixed& other) const { return num != other.num;}

Fixed Fixed::operator+(const Fixed& other) const {
	
	Fixed result;
	result.setRawBits(getRawBits() + other.getRawBits());
	return result;
}

Fixed Fixed::operator-(const Fixed& other) const {
	
	Fixed result;
	result.setRawBits(getRawBits() - other.getRawBits());
	return result;
}

Fixed Fixed::operator*(const Fixed& other) const {

	Fixed result;
	long long temp = (long long)getRawBits() * other.getRawBits();
    result.setRawBits(int((temp + (1 << (_nbr - 1))) >> _nbr));
	return result;
}

Fixed Fixed::operator/(const Fixed& other) const {
	
	if (other.getRawBits() == 0) {
		std::cerr << "Error: Division by zero. Returning default value (0)." << std::endl;
        return Fixed(0);
	}
    Fixed result;
    result.setRawBits((getRawBits() << _nbr) / other.getRawBits());
    return result;
}

Fixed& Fixed::operator++() {
	setRawBits(getRawBits() + 1);
	return *this;
}

Fixed Fixed::operator++(int) {
	
	Fixed temp(*this);
	setRawBits(getRawBits() + 1);
	return temp;
}

Fixed& Fixed::operator--() {
	setRawBits(getRawBits() - 1);
	return *this;
}

Fixed Fixed::operator--(int) {
	
	Fixed temp(*this);
	setRawBits(getRawBits() - 1);
	return temp;
}
float Fixed::toFloat(void) const {
	return float(getRawBits()) / (1 << _nbr);
}

int Fixed::toInt(void) const {
	return getRawBits() >> _nbr;
}

Fixed& Fixed::min(Fixed& a, Fixed& b) {

	return (a < b) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
	
	return(a < b) ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b) {

	return (a > b) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
	
	return(a >b) ? a : b;
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed) {
	os << fixed.toFloat();
	return os;
}

Fixed Fixed::abs(const Fixed& value) {

    if(value.num < 0)
        return Fixed(-value.toFloat());
    return value;
}