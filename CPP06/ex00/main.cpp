/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:53:12 by estosche          #+#    #+#             */
/*   Updated: 2024/12/10 13:41:01 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <string>
#include "Scalar.hpp"

int main(int argc, char **argv) {

	if(argc != 2) {
		std::cerr << "Usage: ./converter <literal>" <<std::endl;
		return 1;
	}
	
	ScalarConverter::convert(argv[1]);
	return 0;
}