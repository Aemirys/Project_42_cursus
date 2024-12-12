/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:17:10 by estosche          #+#    #+#             */
/*   Updated: 2024/11/19 11:15:26 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Fixed area(Point const& a, Point const& b, Point const& c) {

	return Fixed::abs((a.getX() * (b.getY() - c.getY())
					 + b.getX() * (c.getY() - a.getY())
					 + c.getX() * (a.getY() - b.getY())) / Fixed(2));
}

bool	bsp(Point const a, Point const b, Point const c, Point const point) {

	Fixed totalArea = area(a, b, c);

	Fixed area1 = area(point, b, c);
	Fixed area2 = area(a, point, c);
	Fixed area3 = area(a, b, point);

	if(totalArea == (area1 + area2 + area3)){

		return area1 > Fixed(0) && area2 > Fixed(0) && area3 > Fixed(0);
	}
	return false;
}