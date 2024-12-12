/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:25:13 by estosche          #+#    #+#             */
/*   Updated: 2024/12/10 09:39:06 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main() {
	
	 try {
		std::cout << "===== Creating Bureaucrat with valid grades =====\n";
		Bureaucrat bouh("Bouh", 42);
		Bureaucrat bob("Bob", 1);
		Bureaucrat sully("Sully", 150);
		std::cout << std::endl;
		std::cout << bouh;
		std::cout << bob;
		std::cout << sully;

		std::cout << "\n===== Testing grade increment =====\n";
		bouh.incrementeGrade();
		std::cout << "Bouh after increment: " << bouh;

		std::cout << "\n===== Testing grade decrement =====\n";
		try {
			sully.decrementGrade();
			std::cout << "Sully after decrement: " << sully << std::endl;
		} catch (const std::exception& e) {
			std::cerr << "Exception caught during decrement: " << e.what() << std::endl;
		}

		std::cout << "\n===== Testing exceptions in constructor =====\n";
		try {
			Bureaucrat high("High", 0);
		} catch (const std::exception& e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}

		try {
			Bureaucrat low("Low", 151);
		} catch (const std::exception& e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}

		std::cout << "\n===== Testing exceptions in grade increment =====\n";
		try {
			bob.incrementeGrade();
		} catch (const std::exception& e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}

		std::cout << "\n===== Testing exceptions in grade decrement =====\n";
		try {
			sully.decrementGrade();
		} catch (const std::exception& e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}

		std::cout << "\n===== Testing copy constructor and assignment =====\n";
		Bureaucrat copyOfAlice(bouh);
		std::cout << "Copy of Bouh: " << copyOfAlice << std::endl;

		Bureaucrat assigned = bob;
		std::cout << "Assigned Bob: " << assigned << std::endl;

		std::cout << "\n===== Testing further decrements and assignments =====\n";
		Bureaucrat leon("Leon", 75);
		std::cout << leon << std::endl;

		try {
			leon.decrementGrade(); // OK
			std::cout << "Dave after decrement: " << leon << std::endl;
		} catch (const std::exception& e) {
			std::cerr << "Exception caught during decrement: " << e.what() << std::endl;
		}

		
		try {
			leon.decrementGrade(); // OK
			std::cout << "Dave after another decrement: " << leon << std::endl;
		} catch (const std::exception& e) {
			std::cerr << "Exception caught during decrement: " << e.what() << std::endl;
		}

		try {
			for (int i = 0; i < 80; ++i) {
				leon.decrementGrade();
			}
		} catch (const std::exception& e) {
			std::cerr << "Exception caught after too many decrements: " << e.what() << std::endl;
		}

	} catch (const std::exception& e) {
		std::cerr << "Unexpected exception: " << e.what() << std::endl;
	}

	return 0;
}