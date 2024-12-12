/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:48:22 by estosche          #+#    #+#             */
/*   Updated: 2024/12/12 14:09:58 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base* generate() {
	std::srand(std::time(0));
	int type = std::rand() % 3;
	switch (type) {
		case 0:
			std::cout << "Generate A" << std::endl;
			return new A();
		case 1:
			std::cout << "Generate B" << std::endl;
			return new B();
		case 2:
			std::cout << "Generate C" << std::endl;
			return new C();
		default:
			return NULL;
	}
}

void identify(Base* p) {
	if (dynamic_cast<A*>(p)) {
        std::cout << "Type is A" << std::endl;
    } else if (dynamic_cast<B*>(p)) {
        std::cout << "Type is B" << std::endl;
    } else if (dynamic_cast<C*>(p)) {
        std::cout << "Type is C" << std::endl;
    } else {
        std::cout << "Unknown type" << std::endl;
    }
}

void identify(Base& p) {
    try { 
		if (dynamic_cast<A*>(&p)){
			 std::cout << "Type is A" << std::endl;
		} else if (dynamic_cast<B*>(&p)) {
			  std::cout << "Type is B" << std::endl;
		} else if (dynamic_cast<C*>(&p)) {
			std::cout << "Type is C" << std::endl;
		} else {
			std::cout << "Unknown type" << std::endl;
		}      
    } catch (...) {}

}

int main() {
	Base* instance = generate();
	Base* p = NULL;

	std::cout << color << "\n=== Pointer generate ===" << resetcolor << std::endl;
	std::cout << "Identify using pointer: ";
	identify(instance);

	std::cout << "Identify using reference: ";
	identify(*instance);
	
	std::cout << color << "\n=== Pointer NULL ===" << resetcolor << std::endl;
	std::cout << "Identify using pointer: ";
	identify(p);
	std::cout << "Identify using reference: ";
	identify(*p);

	delete instance;
	
	return 0;
}