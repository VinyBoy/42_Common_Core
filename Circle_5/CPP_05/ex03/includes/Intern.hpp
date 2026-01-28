/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:08:25 by viny              #+#    #+#             */
/*   Updated: 2025/11/13 19:42:19 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"


class Intern
{
	public :
		Intern();
		~Intern();
		Intern(const Intern &cpy);
		Intern & operator=(const Intern &assign);
	
		class BadNameException : public std::exception
		{
			const char *what() const throw() {
			return ("Error: Unknown for name"); }
		};

		AForm * makeForm(const std::string & formName, const std::string &targetForm);
};