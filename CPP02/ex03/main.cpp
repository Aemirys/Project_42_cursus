/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:14:06 by estosche          #+#    #+#             */
/*   Updated: 2024/11/21 13:19:23 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

int	main() {

	Point a;
	Point b(Fixed(10), Fixed(0));
	Point c(Fixed(0), Fixed(10));
	Point point(Fixed(2), Fixed(2));

	if (bsp(a, b, c, point)) {
		
		std::cout << "Point is inside the triangle." << std::endl;
	} else {
		std::cout << "Point is outside the triangle." << std::endl;
	}
	
	return 0;
}