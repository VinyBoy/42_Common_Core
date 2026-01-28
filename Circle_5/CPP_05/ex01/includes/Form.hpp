/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:11:35 by viny              #+#    #+#             */
/*   Updated: 2025/11/13 19:41:35 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "./Bureaucrat.hpp"
#include <ostream>

class Bureaucrat;

class Form
{
	public :
		Form();
		Form(std::string name, int requiredGrade, int executeGrade);
		~Form();
		Form(const Form &cpy);
		Form & operator=(const Form &assign);

		class GradeTooHighException : public std::exception
		{
			const char *what() const throw(){
				return ("Grade too high");
			}
		};

		class GradeTooLowException : public std::exception
		{
			const char *what() const throw() {
				return ("Grade too low");
			}
		};
		
		std::string getName() const;
		bool getSigned() const;
		int	getRequieredGrade() const;
		int	getExecuteGrade() const;
		
		bool beSigned(const Bureaucrat &instance);

	private :
		const std::string 	_name;
		bool				_signed;
		int					_requieredGrade;
		int					_executeGrade;

};

std::ostream & operator <<(std::ostream &os, Form const &form);