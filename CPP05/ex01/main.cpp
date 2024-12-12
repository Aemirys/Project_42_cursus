/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:25:13 by estosche          #+#    #+#             */
/*   Updated: 2024/12/10 09:56:33 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

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
		Bureaucrat copyOfBouh(bouh);
		std::cout << "Copy of bouh: " << copyOfBouh << std::endl;

		Bureaucrat assigned = bob;
		std::cout << "Assigned Bob: " << assigned;

		std::cout << "\n===== Testing further decrements and assignments =====\n";
		Bureaucrat leon("leon", 75);
		std::cout << leon << std::endl;

		try {
			leon.decrementGrade();
			std::cout << "Leon after decrement: " << leon << std::endl;
		} catch (const std::exception& e) {
			std::cerr << "Exception caught during decrement: " << e.what() << std::endl;
		}

		try {
			leon.decrementGrade();
			std::cout << "Leon after another decrement: " << leon << std::endl;
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

		std::cout << "\n===== Testing Form =====\n";
		try {
			Bureaucrat germaine("Germaine", 50);
			Form taxForm("Tax Form", 45, 30);

			std::cout << germaine << std::endl;
			std::cout << taxForm << std::endl;

			germaine.signForm(taxForm);
			std::cout << taxForm << std::endl;

			Bureaucrat celia("Celia", 40);
			std::cout << celia;
			celia.signForm(taxForm);
			std::cout << "\n";
		}
		catch (const std::exception& e){
			std::cerr << "Error: " << e.what() << std::endl;
		}
		std::cout << "\n===== Testing Form Copy Constructor and Assignment =====\n";
		try {

			Form originalForm("Original Form", 25, 10);
			std::cout << "Original Form: " << originalForm << std::endl;
			std::cout << "\n";

			Form copiedForm(originalForm);
			std::cout << "Copied Form: " << copiedForm << std::endl;
			std::cout << "\n";

			Form assignedForm("Temp Form", 100, 50);
			std::cout << "Assigned Form before assignment: " << assignedForm << std::endl;
			std::cout << "\n";
			assignedForm = originalForm;
			std::cout << "Assigned Form after assignment: " << assignedForm << std::endl;
			std::cout << "\n";

			Bureaucrat henry("Henry", 20);
			henry.signForm(originalForm);
			std::cout << "Original Form after being signed: " << originalForm << std::endl;
			std::cout << "Copied Form (unchanged): " << copiedForm << std::endl;
			std::cout << "Assigned Form (unchanged): " << assignedForm << std::endl;
			std::cout << "\n";
		} catch (const std::exception& e) {
			std::cerr << "Exception caught during Form copy/assignment tests: " << e.what() << std::endl;
		}

	} catch (const std::exception& e) {
		std::cerr << "Unexpected exception: " << e.what() << std::endl;
	}

	return 0;
}