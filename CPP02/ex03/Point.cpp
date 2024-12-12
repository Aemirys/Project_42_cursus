/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:16:52 by estosche          #+#    #+#             */
/*   Updated: 2024/11/21 13:21:13 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point() : x(0), y(0) {
    std::cout << "Point Default constructor called" << std::endl;
}

Point::Point(const Fixed x, const Fixed y) : x(Fixed(x)), y(Fixed(y)) {
    std::cout << "Point Parametrized constructor called" << std::endl;
}

Point::Point(const Point& other) : x(other.x), y(other.y) {
    std::cout << "Point Copy constructeur called" << std::endl;
}

Point& Point::operator=(const Point& other) {
    std::cout << "Point Copy assignement operator called" << std::endl;
    (void)other;
    return *this;
}

Point::~Point() {
    std::cout << "Point Desructor called" << std::endl;
}

Fixed Point::getX() const {
    return x;
}

Fixed Point::getY() const {
    return y;
}