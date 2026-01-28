/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 07:21:59 by viny              #+#    #+#             */
/*   Updated: 2025/09/11 16:13:17 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONG_ANIMAL_HPP
#define WRONG_ANIMAL_HPP

#include <iostream>

class WrongAnimal
{
	public :
		WrongAnimal(void);
		WrongAnimal(const std::string &type);
		virtual ~WrongAnimal(void);
		WrongAnimal(const WrongAnimal &cpy);
		WrongAnimal & operator=(const WrongAnimal &assign);

		std::string getType(void) const;
		void		setType(std::string const &type);
		
		void	makeSound() const;
	
	protected :
		std::string _type;
	
};

#endif