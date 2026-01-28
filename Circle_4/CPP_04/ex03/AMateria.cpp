/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:53:18 by viny              #+#    #+#             */
/*   Updated: 2025/10/13 17:39:42 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"
#include <iostream>

AMateria::AMateria(void) : _type("")
{
	return;
}

AMateria::~AMateria(void)
{
	return;
}

AMateria::AMateria(const AMateria &cpy) : _type(cpy._type)
{
}

AMateria & AMateria::operator=(const AMateria & assign)
{
	if (this != &assign)
		this->_type = assign._type;
	return (*this);
}

AMateria::AMateria(std::string const & type) : _type(type)
{
	return ;
}

std::string const &AMateria::getType(void) const
{
	return (_type);
}

void AMateria::use(ICharacter& target)
{
	(void)target;
}
