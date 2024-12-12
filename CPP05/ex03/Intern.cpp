/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:36:18 by estosche          #+#    #+#             */
/*   Updated: 2024/12/10 10:08:49 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern() {
	std::cout << "Intern created." << std::endl;
}

Intern::~Intern() {
	std::cout << "Intern destroyed." << std::endl;
}

Intern::Intern(const Intern& other) {
	(void)other;
	std::cout << "Intern copied" << std::endl;
}

Intern& Intern::operator=(const Intern& other) {
	(void)other;
	std::cout << "Intern assigned" << std::endl;
	return *this;
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) const {
	struct FormCreator {
		std::string name;
		AForm* (Intern::*create)(const std::string&) const;
	};


	static const FormCreator formCreators[] = {
		{"shrubbery creation", &Intern::createShrubberyForm},
		{"robotomy request", &Intern::createRobotomyForm},
		{"presidential pardon", &Intern::createPresidentialForm}
	};

	for (size_t i = 0; i < sizeof(formCreators) / sizeof(FormCreator); ++i) {
		if (formCreators[i].name == formName) {
			std::cout << "Intern creates " << formName << std::endl;
			return (this->*formCreators[i].create)(target);
		}
	}

	std::cerr << "Error: Form '" << formName << "' does not exist." << std::endl;
	return NULL;
}

AForm* Intern::createShrubberyForm(const std::string& target) const {
	return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomyForm(const std::string& target) const {
	return new RobotomyRequestForm(target);
}

AForm* Intern::createPresidentialForm(const std::string& target) const {
	return new PresidentialPardonForm(target);
}