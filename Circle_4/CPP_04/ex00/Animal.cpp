/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 07:35:56 by viny              #+#    #+#             */
/*   Updated: 2025/09/11 15:42:58 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal(void) : _type()
{
	std::cout << "Constructor from Animal called : " << _type << std::endl;
	return;
}

Animal::Animal(const std::string &type) : _type(type)
{
	std::cout << "Constructor from Animal called : " << _type << std::endl;
	return;
}

Animal::~Animal(void)
{
	std::cout << "Destructor from Animal called : " << _type << std::endl;
	return ;
}

Animal::Animal(const Animal &cpy)
{
	std::cout << "Copy operator from animal called :" << _type << std::endl;
	_type = cpy._type;
	return;
}

Animal &Animal::operator=(const Animal &assign)
{
	if (&assign != this)
		_type = assign._type;
	std::cout << "Assignement operator from animal called :" << _type << std::endl;
	return (*this);
}

std::string Animal::getType(void) const
{
	return (_type);
}

void	Animal::setType(std::string const &type)
{
	_type = type;
}

void	Animal::makeSound(void) const
{
	std::string AnimalCry;

	if (this->getType() == "Cat")
		AnimalCry = "Meooooooooooow";
	else if (this->getType() == "Dog")
		AnimalCry = "WouuufWouuuf";
	else
		AnimalCry = "Unreconigned AnimalCry";
	std::cout << _type << " : " << AnimalCry << std::endl;
}
