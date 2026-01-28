/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:43:42 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/09/15 13:46:32 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void)
{
    std::cout << "Cat default destructor called" << std::endl;
    return ;
}

Cat::~Cat(void)
{
    std::cout << "Cat destructor called" << std::endl;
    return;
}

Cat::Cat(const Cat & cpy) : Animal(cpy)
{
    std::cout << "Copy constructor called" << std::endl;
    this->_type = cpy._type;
    return ;
}

Cat &Cat::operator=(const Cat &assign)
{
    std::cout << "Assignement operator called" << std::endl;
    if (&assign != this)
        _type = assign._type;
    return (*this);
}

void    Cat::makeSound(void) const
{
    std::cout << "Cat inheritance say : Meow" << std::endl;
}