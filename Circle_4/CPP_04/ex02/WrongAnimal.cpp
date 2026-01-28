/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongWrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 07:35:56 by viny              #+#    #+#             */
/*   Updated: 2025/09/16 18:58:03 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void) : _type()
{
	std::cout << "Constructor from WrongAnimal called : " << _type << std::endl;
	return;
}

WrongAnimal::WrongAnimal(const std::string &type) : _type(type)
{
	std::cout << "Constructor from WrongAnimal called : " << _type << std::endl;
	return;
}

WrongAnimal::~WrongAnimal(void)
{
	std::cout << "Destructor from WrongAnimal called : " << _type << std::endl;
	return ;
}

WrongAnimal::WrongAnimal(const WrongAnimal &cpy)
{
	std::cout << "Copy operator from Wronganimal called :" << _type << std::endl;
	_type = cpy._type;
	return;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &assign)
{
	if (&assign != this)
		_type = assign._type;
	std::cout << "Assignement operator from Wronganimal called :" << _type << std::endl;
	return (*this);
}

std::string WrongAnimal::getType(void) const
{
	return (_type);
}

void	WrongAnimal::setType(std::string const &type)
{
	_type = type;
}

void	WrongAnimal::makeSound(void) const
{
	std::string WrongAnimalCry;

	if (this->getType() == "Cat")
		WrongAnimalCry = "Meooooooooooow";
	else if (this->getType() == "Dog")
		WrongAnimalCry = "WouuufWouuuf";
	else
		WrongAnimalCry = "Unreconigned WrongAnimalCry";
	std::cout << _type << " : " << WrongAnimalCry << std::endl;
}
