/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:40 by viny              #+#    #+#             */
/*   Updated: 2025/11/12 11:51:06 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PresidentialPardonForm.hpp"

#include <iostream>

PresidentialPardonForm::PresidentialPardonForm() : AForm("PresidentialPArdonForm", 25, 5),
_target("default") {}

PresidentialPardonForm::~PresidentialPardonForm() {}

PresidentialPardonForm::PresidentialPardonForm(std::string target) :
AForm("PresidentialPArdonForm", 25, 5),
_target(target) {}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm & cpy) : AForm(cpy),
_target(cpy._target) {}

PresidentialPardonForm & PresidentialPardonForm::operator=(PresidentialPardonForm &assign)
{
	if (this != &assign)
	{
		AForm::operator=(assign);
		_target = assign._target;
	}
	return (*this);
}

const std::string	PresidentialPardonForm::getTarget() const { return (_target); }

void	PresidentialPardonForm::executeAction() const
{
	std::cout << " " << this->getTarget() << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}