/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:09:21 by viny              #+#    #+#             */
/*   Updated: 2025/11/11 18:18:47 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Form.hpp"

Form::Form() : _name("default"), _signed(false), _requieredGrade(150), _executeGrade(150) {}

Form::~Form() {}

Form::Form(std::string name, int requieredGrade, int executeGrade) :
_name(name),
_signed(false),
_requieredGrade(requieredGrade),
_executeGrade(executeGrade)
{
	if (requieredGrade < 1 || executeGrade < 1)
		throw GradeTooHighException();
	if (requieredGrade > 150 || executeGrade > 150)
		throw GradeTooLowException();
}

Form::Form(const Form &cpy) :
_name(cpy._name),
_signed(cpy._signed),
_requieredGrade(cpy._requieredGrade),
_executeGrade(cpy._executeGrade) {}

Form & Form::operator=(const Form &assign)
{
	if (this != &assign)
		_signed = assign._signed;
	return (*this);
}

std::string Form::getName () const { return _name; }
bool Form::getSigned() const { return _signed; }
int	Form::getRequieredGrade() const { return _requieredGrade; }
int	Form::getExecuteGrade() const { return _executeGrade; }

bool Form::beSigned(const Bureaucrat &instance)
{
	if (instance.getGrade() > _requieredGrade)
		throw GradeTooLowException();
	_signed = true;
	return (true);
}

std::ostream & operator<<(std::ostream &os, Form const &form)
{
	os 	<< "Form " << form.getName()
		<< " [signed : " << (form.getSigned()? "yes" : "no")
		<< ", grade to sign : " << form.getRequieredGrade()
		<< ", grade to execute : " << form.getExecuteGrade() << "]";
	return (os);
}