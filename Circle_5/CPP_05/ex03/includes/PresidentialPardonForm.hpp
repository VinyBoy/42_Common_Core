/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:33:40 by viny              #+#    #+#             */
/*   Updated: 2025/11/13 19:15:36 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./AForm.hpp"
#include <string>

class PresidentialPardonForm : public AForm
{
	public :
		PresidentialPardonForm();
		virtual ~PresidentialPardonForm();
		PresidentialPardonForm(const std::string &target);
		PresidentialPardonForm(const PresidentialPardonForm &cpy);
		PresidentialPardonForm & operator=(const PresidentialPardonForm &assign);
		
		const std::string getTarget() const;
	
	protected :
		virtual void executeAction() const;

	private :
		std::string _target;
};