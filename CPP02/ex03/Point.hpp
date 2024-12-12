/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:16:05 by estosche          #+#    #+#             */
/*   Updated: 2024/11/19 11:21:49 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

class Point {
	
	private:
		const Fixed  x;
		const Fixed  y;
	public:
		Point();
		Point(const Fixed x, const Fixed y);
		Point(const Point& other);
		~Point();
		Point& operator=(const Point& other);
		Fixed getX()const;
		Fixed getY() const;
};

bool	bsp(Point const a, Point const b, Point const c, Point const Point);
#endif