/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:24:48 by viny              #+#    #+#             */
/*   Updated: 2025/11/13 19:42:50 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Bureaucrat.hpp"
#include "./includes/AForm.hpp"
#include "./includes/PresidentialPardonForm.hpp"
#include "./includes/RobotomyRequestForm.hpp"
#include "./includes/ShrubberyCreationForm.hpp"
#include "./includes/Intern.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime> 


int main()
{
	srand(time(NULL));
	std::cout << "\n---- Intern 1 ----\n" << std::endl;
	try
	{
    	Intern someRandomIntern;
		Bureaucrat Boss("Boss", 1);
		
   		AForm* rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		Boss.signForm(*rrf);
		Boss.executeForm(*rrf);
		delete rrf;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << "\n---- Intern 2 ----\n" << std::endl;
	try
	{
    	Intern someRandomIntern;
		Bureaucrat Boss("Boss", 1);
		
   		AForm* rrf = someRandomIntern.makeForm("shrubbery creation", "Bender");
		Boss.signForm(*rrf);
		Boss.executeForm(*rrf);
		delete rrf;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << "\n---- Intern 3 ----\n" << std::endl;	
	try
	{
    	Intern someRandomIntern;
		Bureaucrat Boss("Boss", 1);
		
   		AForm* rrf = someRandomIntern.makeForm("presidential pardon", "Bender");
		Boss.signForm(*rrf);
		Boss.executeForm(*rrf);
		delete rrf;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << "\n---- Intern 4 (invalid)----\n" << std::endl;
	try
	{
    	Intern someRandomIntern;
		Bureaucrat Boss("Boss", 1);
		
   		AForm* rrf = someRandomIntern.makeForm("Nimp", "Bender");
		Boss.signForm(*rrf);
		Boss.executeForm(*rrf);
		delete rrf;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);	
}