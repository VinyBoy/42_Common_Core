/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:24:48 by viny              #+#    #+#             */
/*   Updated: 2025/11/12 12:52:02 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Bureaucrat.hpp"
#include "./includes/AForm.hpp"
#include "./includes/PresidentialPardonForm.hpp"
#include "./includes/RobotomyRequestForm.hpp"
#include "./includes/ShrubberyCreationForm.hpp"
#include <iostream>
#include <string>
#include <cstdlib>

// static void	WelcomeBureaucrat(const Bureaucrat &instance)
// {
// 	std::cout	<< "Welcome " << instance.getName() << " your grade is : "  
// 				<< instance.getGrade() << std::endl;
// }

// static void changeGrade(Bureaucrat &instance, int newGrade)
// {
// 	if (newGrade < 1 || newGrade > 150)
// 	{
// 		std::cout << "Error : Grade sould be between 1 and 150\n";
// 		return ;
// 	}
// 	std::cout	<< "Now " << instance.getName() << " have "  
// 				<< instance.getGrade() << " of grade" << std::endl;
		
// 	if (instance.getGrade() != newGrade)
// 	{
// 		if (instance.getGrade() < newGrade)
// 			while (instance.getGrade() != newGrade)
// 				instance.decrement();
// 		else
// 		{
// 			while (instance.getGrade() != newGrade)
// 				instance.increment();
// 		}
// 	}
// 	else
// 		std::cout << "Error : Same grade, don't need to change";
// 	std::cout	<< "New grade for " << instance.getName() << " is " << instance.getGrade()
// 				<< "\n" << std::endl;
// }

int main()
{
	std::cout << "---- Test Shrubbery ----\n" << std::endl;
	try
	{
		Bureaucrat Designer("Designer", 100);
		ShrubberyCreationForm AsciiTree("President");
		Designer.signForm(AsciiTree);
		std::cout << "\nHi President i Have a gift for you" << std::endl;
		Designer.executeForm(AsciiTree);
	}
	catch(const std::exception& e)
	{
		std::cout << "Error :" << e.what() << std::endl;
	}
	srand(time(NULL));
	std::cout << "\n---- Test RobotomyRequestForm ----\n" << std::endl;
	try
	{
		Bureaucrat CoPresident("CoPresident", 2);
		RobotomyRequestForm Robotize("Docteur Jeckyl");
		CoPresident.signForm(Robotize);
		CoPresident.executeForm(Robotize);	
	} catch (std::exception &e)
	{
		std::cout << "Error : " << e.what();
	}
	std::cout << "\n---- Test President ----\n" << std::endl;
	try
	{
		Bureaucrat president("President", 1);
		PresidentialPardonForm pardon("Mr Hyde");
		
		president.signForm(pardon);
		president.executeForm(pardon);
	} catch (std::exception &e)
	{
		std::cout << "Error : " << e.what() << std::endl;
	}
	return (0);	
}