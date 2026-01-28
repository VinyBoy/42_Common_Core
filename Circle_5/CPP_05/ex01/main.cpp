/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:24:48 by viny              #+#    #+#             */
/*   Updated: 2025/11/13 19:44:30 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Bureaucrat.hpp"
#include "./includes/Form.hpp"
#include <iostream>
#include <string>

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
		std::cout << Henri;
		WelcomeBureaucrat(Henri);
		Bureaucrat Salavador("Salvador", 3);
		WelcomeBureaucrat(Salavador);
		changeGrade(Salavador, 2);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	
	std::cout << "---- Test valid Form---- \n" << std::endl;
	try
	{
		Form one("One", 30, 50);
		Bureaucrat Jones("Jones", 30);
		one.beSigned(Jones);
		std::cout << one << "\n" << std::endl;
	} catch (std::exception &e)
	{
		std::cout << e.what();
	}
	std::cout << "---- Test invalid Form---- \n" << std::endl;
	try
	{
		Form two("Two", 20, 50);
		Bureaucrat BizzyJones("Bizzy Jones", 21);
		two.beSigned(BizzyJones);
		std::cout << two << "\n" << std::endl;
	} catch (std::exception &e)
	{
		std::cout << e.what();
	}

	std::cout << "\n\n---- Test 1 beSigned / signForm ----\n" << std::endl;
	try
	{
		Form test("test", 20, 20);
		Bureaucrat Yng("Yng", 30);
		Yng.signForm(test);
	} catch (std::exception &e)
	{
		std::cout << e.what();
	}

	std::cout << "\n\n---- Test 2 beSigned / signForm ----\n" << std::endl;
	try
	{
		Form test2("test2", 20, 20);
		Bureaucrat Yng2("Yng2", 20);
		Yng2.signForm(test2);
	} catch (std::exception &e)
	{
		std::cout << e.what();
	}
	return (0);
}