/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 07:21:59 by viny              #+#    #+#             */
/*   Updated: 2025/09/16 15:48:31 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>

class Animal
{
	public :
		Animal(void);
		Animal(const std::string &type);
		virtual ~Animal(void);
		Animal(const Animal &cpy);
		Animal & operator=(const Animal &assign);

		std::string getType(void) const;
		void		setType(std::string const &type);
		
		virtual void	makeSound() const = 0;
	
	protected :
		std::string _type;
	
};

#endif