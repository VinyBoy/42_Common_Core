/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:43:52 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/09/15 13:46:50 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void)
{
    std::cout << "Dog default destructor called" << std::endl;
    return ;
}

Dog::~Dog(void)
{
    std::cout << "Dog destructor called" << std::endl;
    return;
}

Dog::Dog(const Dog &cpy) : Animal(cpy)
{
    std::cout << "Copy constructor called" << std::endl;
    this->_type = cpy._type;
    return ;
}

Dog &Dog::operator=(const Dog &assign)
{
    std::cout << "Assignement operator called" << std::endl;
    if (&assign != this)
        _type = assign._type;
    return (*this);
}

void    Dog::makeSound(void) const
{
    std::cout << "Dog inheritance say WoufWouf" << std::endl;
}