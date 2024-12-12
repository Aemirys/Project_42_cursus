/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:25:08 by estosche          #+#    #+#             */
/*   Updated: 2024/12/09 12:00:39 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm(const std::string name, int gradeToSign, int gradeToExecute, const std::string target)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute),  _target(target) {
	std::cout << "AForm: " << _name << " is constructed" << std::endl;
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw GradeTooLowException();
}

AForm::AForm(const AForm& other)
	: _name(other._name), _isSigned(other._isSigned), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {
		std::cout << "AForm: " << _name << " is copied!" << std::endl;
}


AForm& AForm::operator=(const AForm& other) {
	std::cout << "AForm: " << _name << " assigned!" << std::endl;
	if(this != &other) {
		 _isSigned= other._isSigned;
		 _target = other._target;
	}   
	return *this;
}

AForm::~AForm() {
	std::cout << "AForm: " << _name << " is destroyed!" << std::endl;
}

std::string const &AForm::getName() const{
	return _name;
}

bool AForm::isSigned() const {
	return _isSigned;
}

int AForm::getGradeToSign() const {
	return _gradeToSign;
}

int AForm::getGradeToExecute() const {
	return _gradeToExecute;
}

void AForm::beSigned(const Bureaucrat& bureaucrat) {
	if(bureaucrat.getGrade() > _gradeToSign)
		throw GradeTooLowException();
	_isSigned = true;
}

const char* AForm::GradeTooHighException:: what() const throw() {
	return " Form grade is too hignt!";
}

const char* AForm::GradeTooLowException:: what() const throw() {
	return " Form grade is too low!";
}

const char* AForm::FormNotSignedException::what() const throw() {
	return " Form is not signed";
}

std::string  AForm::getTarget() const {
	return _target;
}

std::ostream& operator<<(std:: ostream&out, const AForm& AForm) {
	out << "Form: " << AForm.getName()
		<< ", Signed: " << (AForm.isSigned() ? "Yes" : "NO")
		<< ", Grade to Sign: " << AForm.getGradeToSign()
		<< ", Grade to Execute: " << AForm.getGradeToExecute();
		return out;
}