/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:25:08 by estosche          #+#    #+#             */
/*   Updated: 2024/12/10 09:59:57 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form(const std::string&  name, int gradeToSign, int gradeToExecute)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
	std::cout << "Form: " << _name << " is constructed" << std::endl;
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw GradeTooLowException();
}

Form::Form(const Form& other)
	: _name(other._name), _isSigned(other._isSigned), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {
		std::cout << "Form: " << _name << " is copied!" << std::endl;
}

Form& Form::operator=(const Form& other) {
	std::cout << "Form: " << _name << " assigned!" << std::endl;
	if(this != &other)
		_isSigned= other._isSigned;
	return *this;
}

Form::~Form() {
	std::cout << "Form: " << _name << " is destroyed!" << std::endl;
}

std::string Form::getName() const {
	return _name;
}

bool Form::isSigned() const {
	return _isSigned;
}

int Form::getGradeToSign() const {
	return _gradeToSign;
}

int Form::getGradeToExecute() const {
	return _gradeToExecute;
}

void Form::beSigned(const Bureaucrat& bureaucrat) {
	if(bureaucrat.getGrade() > _gradeToSign)
		throw GradeTooLowException();
	_isSigned = true;
}

const char* Form::GradeTooHighException:: what() const throw() {
	return "Form grade is too hignt!";
}

const char* Form::GradeTooLowException:: what() const throw() {
	return "Form grade is too low!";
}

std::ostream& operator<<(std:: ostream&out, const Form& form) {
	out << "Form: " << form.getName()
		<< ", Signed: " << (form.isSigned() ? "Yes" : "NO")
		<< ", Grade to Sign: " << form.getGradeToSign()
		<< ", Grade to Execute: " << form.getGradeToExecute();
		return out;
}