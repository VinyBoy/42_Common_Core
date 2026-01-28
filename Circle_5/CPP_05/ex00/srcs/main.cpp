/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:27:29 by viny              #+#    #+#             */
/*   Updated: 2025/11/11 13:25:33 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Bureaucrat.hpp"
#include <iostream>

static void	WelcomeBureaucrat(const Bureaucrat &instance)
{
	std::cout	<< "Welcome " << instance.getName() << " your grade is : "  
				<< instance.getGrade() << std::endl;
}

static void changeGrade(Bureaucrat &instance, int newGrade)
{
	if (newGrade < 1 || newGrade > 150)
	{
		std::cout << "Error : Grade sould be between 1 and 150\n";
		return ;
	}
	std::cout	<< "Now " << instance.getName() << " have "  
				<< instance.getGrade() << " of grade" << std::endl;
		
	if (instance.getGrade() != newGrade)
	{
		if (instance.getGrade() < newGrade)
			while (instance.getGrade() != newGrade)
				instance.decrement();
		else
		{
			while (instance.getGrade() != newGrade)
				instance.increment();
		}
	}
	else
		std::cout << "Error : Same grade, don't need to change";
	std::cout	<< "New grade for " << instance.getName() << " is " << instance.getGrade()
				<< "\n" << std::endl;
}

int main()
{
	std::cout << "---- Declaraton de Bureaucrat ----\n" << std::endl;
	try 
	{
		Bureaucrat Henri("Henri", 20);
		WelcomeBureaucrat(Henri);
		Bureaucrat Salavador("Salvador", 3);
		WelcomeBureaucrat(Salavador);

		std::cout << "\n---- Test grade ----\n" << std::endl;;
		changeGrade(Henri, 150);
		changeGrade(Henri, 10);
		changeGrade(Henri, 10);
		changeGrade(Henri, -1);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	
	try
	{
		std::cout << "\n---- Test exception Hight----\n" << std::endl;
		Bureaucrat Test("Test", -1);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	try
	{
		std::cout << "\n---- Test exception Low----\n" << std::endl;
		Bureaucrat Test2("Test2", 151);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return (0);
}