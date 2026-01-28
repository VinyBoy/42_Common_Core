/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:40 by viny              #+#    #+#             */
/*   Updated: 2025/11/13 19:36:51 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PresidentialPardonForm.hpp"

#include <iostream>

PresidentialPardonForm::PresidentialPardonForm() : AForm("PresidentialPardonForm", 25, 5),
_target("default") {}

PresidentialPardonForm::~PresidentialPardonForm() {}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target) :
AForm("PresidentialPardonForm", 25, 5),
_target(target) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm & cpy) : AForm(cpy),
_target(cpy._target) {}

PresidentialPardonForm & PresidentialPardonForm::operator=(const PresidentialPardonForm &assign)
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