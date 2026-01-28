/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:53:30 by viny              #+#    #+#             */
/*   Updated: 2025/10/13 17:41:00 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"
#include "ICharacter.hpp"
#include <iostream>

Ice::Ice() : AMateria("ice")
{
	return ;
}

Ice::Ice(const Ice &cpy) : AMateria(cpy)
{
	return ;
}

Ice & Ice::operator=(const Ice &assign)
{
	if (this != &assign)
	{
		AMateria::operator=(assign);
	}
	return (*this);
}

Ice::~Ice()
{
	return ;
}

AMateria *Ice::clone() const
{
	return (new Ice(*this));
}
void Ice::use(ICharacter &target)
{
	std::cout << " * shoots an ice bolt at " << target.getName() << " *" << std::endl;
	return ;
}