/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:09:21 by viny              #+#    #+#             */
/*   Updated: 2025/11/11 18:18:32 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/AForm.hpp"

AForm::AForm() : _name("default"), _signed(false), _requieredGrade(150), _executeGrade(150) {}

AForm::~AForm() {}

AForm::AForm(std::string name, int requieredGrade, int executeGrade) :
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

AForm::AForm(const AForm &cpy) :
_name(cpy._name),
_signed(cpy._signed),
_requieredGrade(cpy._requieredGrade),
_executeGrade(cpy._executeGrade) {}

AForm & AForm::operator=(const AForm &assign)
{
	if (this != &assign)
		_signed = assign._signed;
	return (*this);
}

std::string AForm::getName () const { return _name; }
bool AForm::getSigned() const { return _signed; }
int	AForm::getRequieredGrade() const { return _requieredGrade; }
int	AForm::getExecuteGrade() const { return _executeGrade; }

bool AForm::beSigned(const Bureaucrat &instance)
{
	if (instance.getGrade() > _requieredGrade)
		throw GradeTooLowException();
	_signed = true;
	return (true);
}

void AForm::execute(Bureaucrat const &executor) const
{
	if (!_signed)
		throw FormNotSignedException();
	if (executor.getGrade() > this->_executeGrade)
		throw GradeTooLowException();
	executeAction();
}

std::ostream & operator<<(std::ostream &os, AForm const &form)
{
	os 	<< "Form " << form.getName()
		<< " [signed : " << (form.getSigned()? "yes" : "no")
		<< ", grade to sign : " << form.getRequieredGrade()
		<< ", grade to execute : " << form.getExecuteGrade() << "]";
	return (os);
}