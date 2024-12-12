/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:29:16 by estosche          #+#    #+#             */
/*   Updated: 2024/12/09 16:53:00 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main() {
	try {
		std::cout << "===== Creating Bureaucrats =====\n";
		Bureaucrat bouh("Bouh", 42);
		Bureaucrat bob("Bob", 1);
		Bureaucrat sully("Sully", 150);
		std::cout << bouh << bob << sully;

		std::cout << "\n===== Testing exceptions in Bureaucrat =====\n";
		try {
			Bureaucrat tooHigh("TooHigh", 0);
		} catch (const std::exception& e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}

		try {
			Bureaucrat tooLow("TooLow", 151);
		} catch (const std::exception& e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}

		std::cout << "\n===== Testing ShrubberyCreationForm =====\n";
		try {
			ShrubberyCreationForm shrubbery("Home");
			std::cout << shrubbery << std::endl;

			bob.signForm(shrubbery);
			bob.executeForm(shrubbery);
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}

		std::cout << "\n===== Testing RobotomyRequestForm =====\n";
		try {
			RobotomyRequestForm robot("Sully");
			std::cout << robot << std::endl;

			bouh.signForm(robot);
			bouh.executeForm(robot);
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}

		std::cout << "\n===== Testing PresidentialPardonForm =====\n";
		try {
			PresidentialPardonForm pardon("Germaine");
			std::cout << pardon << std::endl;

			bob.signForm(pardon);
			bob.executeForm(pardon);
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}

		std::cout << "\n===== Testing exceptions in Form Execution =====\n";
		try {
			ShrubberyCreationForm shrubbery("Garden");
			sully.executeForm(shrubbery);
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}

		try {
			RobotomyRequestForm robot("Bob");
			bob.signForm(robot);
			sully.executeForm(robot);
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}


		std::cout << "\n===== Testing Intern =====\n";
		Intern someRandomIntern;
		AForm* rrf;

		std::cout << "\n===== Testing Intern Robotomy =====\n";
		try {
			rrf = someRandomIntern.makeForm("robotomy request", "Bender");
			std::cout << *rrf << std::endl;

			bouh.signForm(*rrf);
			bouh.executeForm(*rrf);

			delete rrf;
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}

		std::cout << "\n===== Testing Intern Shrubbery=====\n";
		try {
			rrf = someRandomIntern.makeForm("shrubbery creation", "Wood");
			std::cout << *rrf << std::endl;

			bouh.signForm(*rrf);
			bouh.executeForm(*rrf);

			delete rrf;
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}

		std::cout << "\n===== Testing Intern Presidential =====\n";
		try {
			rrf = someRandomIntern.makeForm("presidential pardon", "Germaine");
			std::cout << *rrf << std::endl;

			bouh.signForm(*rrf);
			bouh.executeForm(*rrf);
			delete rrf;
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}

		std::cout << "\n===== Testing Intern invalid =====\n";
		try {
			rrf = someRandomIntern.makeForm("nonexistent form", "Unknown");
			if (!rrf) {
				std::cout << "Form not created!" << std::endl;
			}
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	} catch (const std::exception& e) {
		std::cerr << "Unexpected exception: " << e.what() << std::endl;
	}

	return 0;
}
