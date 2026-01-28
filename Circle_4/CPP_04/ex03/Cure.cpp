/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:53:23 by viny              #+#    #+#             */
/*   Updated: 2025/10/14 18:17:02 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure() : AMateria("cure")
{
	return;
}

Cure::Cure(const Cure &cpy) : AMateria(cpy)
{
	return ;
}

Cure & Cure::operator=(const Cure &assign)
{
	if (this != &assign)
	{
		AMateria::operator=(assign);
	}
	return (*this);
}

Cure::~Cure()
{
	return ;
}

AMateria * Cure::clone() const
{
	return new Cure(*this);	
}

void	Cure::use(ICharacter &target)
{
	std::cout << " * heals " << target.getName() << " 's wounds *" << std::endl;
}
