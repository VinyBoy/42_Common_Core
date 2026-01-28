/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:28:08 by viny              #+#    #+#             */
/*   Updated: 2025/11/11 16:15:59 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Bureaucrat.hpp"
#include <iostream>

Bureaucrat::Bureaucrat() {}

Bureaucrat::~Bureaucrat() {}

Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name), _grade(grade)
{
	if (grade < 1)
		throw GradeTooHightException();
	if (grade > 150)
		throw GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat &cpy) : _name(cpy._name), _grade(cpy._grade) {}

Bureaucrat & Bureaucrat::operator=(const Bureaucrat &assign)
{
	if (this != &assign)
		_grade = assign._grade;
	return (*this);
}

const std::string Bureaucrat::getName() const
{
	return (_name);
}

int	Bureaucrat::getGrade() const
{
	return (_grade);
}

void Bureaucrat::increment()
{
	if (_grade - 1 < 1)
		throw GradeTooHightException();
	_grade--;
}

void Bureaucrat::decrement()
{
	if (_grade + 1 > 150)
		throw GradeTooLowException();
	 _grade++;
}

std::ostream & operator<<(std::ostream &os, Bureaucrat const &instance)
{
	os	<< instance.getName() << " bureaucrate grade : " << instance.getGrade()
		<< std::endl;
	return (os);
}

void Bureaucrat::signForm(Form &form)
{
	try 
	{
		form.beSigned(*this);
		std::cout << this->getName() << " signed " << form.getName(); 
	}
	catch (std::exception &e)
	{
		std::cout	<< this->getName() << " couldn’t sign "
					<< form.getName() << " because " << e.what();
	}
}