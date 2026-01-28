/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:26:13 by viny              #+#    #+#             */
/*   Updated: 2025/11/13 19:41:31 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <exception>
#include "./Form.hpp"

class Form;

class Bureaucrat
{
	public :
		Bureaucrat();
		~Bureaucrat();
		Bureaucrat(std::string name, int grade);
		Bureaucrat(const Bureaucrat &cpy);
		Bureaucrat & operator=(const Bureaucrat &assign);
		
		const std::string getName() const;
		int	getGrade() const ;

		void	increment();
		void	decrement();
		void	signForm(Form &form);

		class GradeTooHightException : public std::exception
		{
			const char *what() const throw() {
				return ("Grade too high"); }
		};
		
		class GradeTooLowException : public std::exception
		{
			const char *what() const throw() {
				return ("Grade too low");
			}
		};
		
	private :
		const std::string 	_name;
		int					_grade;
};

std::ostream & operator<<(std::ostream &os, Bureaucrat const &instance);