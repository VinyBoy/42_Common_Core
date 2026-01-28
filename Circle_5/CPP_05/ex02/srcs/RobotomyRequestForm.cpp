/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:49:13 by viny              #+#    #+#             */
/*   Updated: 2025/11/12 12:09:03 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RobotomyRequestForm.hpp"

#include <iostream>
#include <cstdlib>

RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequestForm", 72, 45),
_target("default") {}

RobotomyRequestForm::RobotomyRequestForm(std::string target) : AForm("RobotomyRequestForm", 72, 45),
_target(target) {}

RobotomyRequestForm::~RobotomyRequestForm() {}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm &cpy) : AForm(cpy),
_target(cpy._target) {}

RobotomyRequestForm & RobotomyRequestForm::operator=(RobotomyRequestForm &assign)
{
	if (this != &assign)
	{
		AForm::operator=(assign);
		_target = assign._target;
	}
	return (*this);
}

const std::string RobotomyRequestForm::getTarget() const { return (_target); }

void RobotomyRequestForm::executeAction() const
{
	std::cout << " * BZZZZZZZZZZZZZ *" << std::endl;
	if (rand() % 2 == 0)
		std::cout << _target << " has been robotized" << std::endl;
	else
		std::cout << "Nothing append to " << _target << std::endl;
}