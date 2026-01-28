/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:21:29 by viny              #+#    #+#             */
/*   Updated: 2025/11/13 19:05:04 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AForm.hpp"
#include <string>

class ShrubberyCreationForm : public AForm
{
	public :
	ShrubberyCreationForm();
	ShrubberyCreationForm(std::string target);
	virtual ~ShrubberyCreationForm();
	ShrubberyCreationForm(ShrubberyCreationForm &cpy);
	ShrubberyCreationForm & operator=(ShrubberyCreationForm &assign);
	
	const std::string getTarget() const;

	virtual void executeAction() const;
	
	private :
		std::string _target;	
};