/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:03:56 by estosche          #+#    #+#             */
/*   Updated: 2024/12/09 15:11:58 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string target)
	: AForm("RobotomyRequestForm", 72, 45, target), _target(target) {}

RobotomyRequestForm::~RobotomyRequestForm() {}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const {
	 if (!this->isSigned()) {
		throw FormNotSignedException();
	}
	if (executor.getGrade() > this->getGradeToExecute()) {
		throw GradeTooLowException();
	}

	std::cout << "Drilling noises... "<< std::endl;
	srand(time(0));
	int success = rand() % 2;

	std::cout << "Robotomizing " << _target << "...\n[";
	for (int i = 0; i < 10; ++i) {
		if (i < 10)
			std::cout << "#";
	}
	std::cout << "] 100%\n";
	if (success == 0) {
		std::cout << _target << " has been robotomized successfully!" << std::endl;
	} else {
		std::cout << "Robotomy failed on " << _target << "." << std::endl;
	}
}