/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:24:30 by viny              #+#    #+#             */
/*   Updated: 2025/11/12 12:49:21 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ShrubberyCreationForm.hpp"

#include <iostream>
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm", 145, 137),
_target("default") {}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : AForm("ShrubberyCreationForm", 145, 137),
_target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm &cpy) : AForm(cpy),
_target(cpy._target) {}

ShrubberyCreationForm & ShrubberyCreationForm::operator=(ShrubberyCreationForm &assign)
{
	if (this != &assign)
	{
		AForm::operator=(assign);
		_target = assign._target;
	}
	return(*this);
}

const std::string ShrubberyCreationForm::getTarget() const { return (_target); }

void	ShrubberyCreationForm::executeAction() const
{
	std::string filename = _target + "_shrubbery";
	
	std::ofstream file(filename.c_str());

	if (!file.is_open())
	{
		std::cerr << "Error file isn't open" << std::endl;
		return ;
	}
	
    file << "        *" << std::endl;
    file << "       ***" << std::endl;
    file << "      *****" << std::endl;
    file << "     *******" << std::endl;
    file << "    *********" << std::endl;
    file << "   ***********" << std::endl;
    file << "       |||   " << std::endl;
    file << "       |||   " << std::endl;
    file << std::endl;
	file.close();
	std::cout << "Shrubbery created in file : " << filename << std::endl;
}
