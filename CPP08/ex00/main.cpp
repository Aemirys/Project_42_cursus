/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:01:23 by estosche          #+#    #+#             */
/*   Updated: 2024/12/18 15:37:23 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

int main() {
	std::cout << color << "\n===== Testing Vector =====\n" << resetcolor;
	std::vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	try {
		std::vector<int>::iterator it = easyfind(vec, 20);
		std::cout << "Found in vector: " << *it << std::endl;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << color << "\n===== Testing list =====\n" << resetcolor;
	std::list<int> lst;
	lst.push_back(100);
	lst.push_back(200);
	lst.push_back(300);
	try {
		std::list<int>::iterator it = easyfind(lst, 200);
		std::cout << "Found in list: " << *it << std::endl;
	}catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << color << "\n===== Testing Vector not found =====\n" << resetcolor;
	try {
		std::vector<int>::iterator it = easyfind(vec, 50);
		std::cout << "Found in vector: " << *it << std::endl;
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}