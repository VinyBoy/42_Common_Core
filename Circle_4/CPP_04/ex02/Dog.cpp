/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:43:52 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/09/16 14:36:39 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void)
{
    std::cout << "Dog default constructor called" << std::endl;
    _Brain = new Brain();
    return ;
}

Dog::~Dog(void)
{
    std::cout << "Dog destructor called" << std::endl;
    delete _Brain;
    return;
}

Dog::Dog(const Dog &cpy) : Animal(cpy)
{
    std::cout << "Copy constructor called" << std::endl;
	if (cpy._Brain)
		_Brain = new Brain(*cpy._Brain);
	else
		_Brain = NULL;
    return ;
}

Dog &Dog::operator=(const Dog &assign)
{
    std::cout << "Assignement operator called" << std::endl;
    if (&assign != this)
    {
        Animal::operator=(assign);
		delete _Brain;
		if (assign._Brain)
			_Brain = new Brain(*assign._Brain);
		else
			_Brain = NULL;
		_type = assign._type;
		
    }
    return (*this);
}

void    Dog::makeSound(void) const
{
    std::cout << "Dog inheritance say : WoufWouf 🐶" << std::endl;
}

Brain* Dog::getBrain() const
{
    return _Brain;
}