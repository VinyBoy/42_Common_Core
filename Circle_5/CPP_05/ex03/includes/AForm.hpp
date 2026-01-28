/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:11:35 by viny              #+#    #+#             */
/*   Updated: 2025/11/13 19:40:57 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "./Bureaucrat.hpp"
#include <ostream>

class Bureaucrat;

class AForm
{
	public :
		AForm();
		AForm(std::string name, int requiredGrade, int executeGrade);
		virtual ~AForm();
		AForm(const AForm &cpy);
		AForm & operator=(const AForm &assign);

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

		class FormNotSignedException : public std::exception
		{
			const char *what() const throw() {
				return ("Form not signed");
			}
		};
		
		std::string getName() const;
		bool getSigned() const;
		int	getRequieredGrade() const;
		int	getExecuteGrade() const;
		
		bool beSigned(const Bureaucrat &instance);

		virtual void execute(Bureaucrat const & executor) const;
		
	protected :
		virtual void executeAction() const = 0;

	private :
		const std::string 	_name;
		bool				_signed;
		int					_requieredGrade;
		int					_executeGrade;

};

std::ostream & operator <<(std::ostream &os, AForm const &form);