/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:04:07 by estosche          #+#    #+#             */
/*   Updated: 2024/12/09 14:49:28 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string target)
	: AForm("ShrubberyCreationForm", 145, 137, target), _target(target) {}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const {
	if (!this->isSigned()) {
		throw FormNotSignedException();
	}
	if (executor.getGrade() > this->getGradeToExecute()) {
		throw GradeTooLowException();
	}

	std::ofstream ofs((this->getTarget() + "_shrubbery").c_str());
	if (ofs){
		ofs << "        *          *         *\n"
			<< "       ^^^        ^^^       ^o^\n"
			<< "      ^^^o^      ^^o^^     ^^^^^\n"
			<< "     ^^^^^^^    ^^^^^^^   ^^^^^^^\n"
			<< "    ^^o^^^^^^  ^o^^^^^^^ ^^^^o^^^^\n"
			<< "   ^^^^^^^^^^^ ^^^^^^o^^^ ^^^^^^^^^\n"
			<< "  ^^^^^^^^^o^^^ ^^^^^^^^^^ ^^^^^o^^^\n"
			<< " ^^^^^^^^^^^^^^^^ ^^^^^^^^^ ^^^^^^^^^\n"
			<< "      |||         |||        |||\n"
			<< "      |||         |||        |||\n";

		std::cout << "Shrubbery has been created at " << this->getTarget() << "_shrubbery" << std::endl;
	} else {
		std::cerr << "Error: Could not create file for " << this->getTarget() << std::endl;
	}
	ofs.close();
}