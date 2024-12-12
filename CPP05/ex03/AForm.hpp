/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:24:40 by estosche          #+#    #+#             */
/*   Updated: 2024/12/09 11:59:47 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
#define AFORM_HPP

#include "Bureaucrat.hpp"
#include <fstream>
#include <iostream>

class Bureaucrat;

class AForm {
	private:
		std::string const _name;
		bool _isSigned;
		const int _gradeToSign;
		const int _gradeToExecute;
		std::string _target;
	protected:
		AForm(std::string name, int gradeTosign, int gradeToExecute, std::string target);
	public:
		AForm(const AForm& other);
		AForm& operator=(const AForm& other);
		virtual ~AForm();
		
		virtual void execute(Bureaucrat const & executor) const = 0;
		std::string const &getName() const;
		bool isSigned() const;
		int getGradeToSign() const;
		int getGradeToExecute() const;
		void beSigned(const Bureaucrat& bureaucrat);
		std::string getTarget() const;
		class GradeTooHighException : public std:: exception {
			public:
				const char* what() const throw();
		};
		class GradeTooLowException : public std::exception {
			public:
				const char* what() const throw();
		};
		class FormNotSignedException : public std::exception {
			const char* what() const throw();
		};
};

std::ostream& operator<<(std::ostream& out, const AForm& AForm);

#endif