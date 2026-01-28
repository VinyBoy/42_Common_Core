/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:07:45 by viny              #+#    #+#             */
/*   Updated: 2025/11/13 19:39:15 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Intern.hpp"
#include <iostream>

Intern::Intern() {}

Intern::~Intern() {}

Intern::Intern(const Intern &cpy) { (void)cpy; }

Intern & Intern::operator=(const Intern &assign)
{
	(void)assign;
	return (*this);
}

static int	recover_index(const std::string &level)
{
	const char *name[3] = {"shrubbery creation",
						"robotomy request",
						"presidential pardon"};
	for (size_t i = 0 ; i < 3; i++)
	{
		if (level == name[i])
			return (i);
	}
	return (-1);
}

AForm *Intern::makeForm(const std::string &formName, const std::string &targetForm)
{
	const int index = recover_index(formName);

	switch (index)
	{
		case 0:
			std::cout << "Shrubbery Creation Form created" << std::endl; 
			return (new ShrubberyCreationForm(targetForm));
		case 1:
			std::cout << "Robotomy Request Form created" << std::endl; 
			return (new RobotomyRequestForm(targetForm));
		case 2 :
			std::cout << "Presidential Pardon Form created" << std::endl; 
			return (new PresidentialPardonForm(targetForm));
		default :
			throw BadNameException();
	}
}