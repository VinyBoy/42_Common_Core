/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:43:42 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/10/14 18:07:08 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void)
{
    std::cout << "Cat default constructor called" << std::endl;
    _Brain = new Brain();
    return ;
}

Cat::~Cat(void)
{
    std::cout << "Cat destructor called" << std::endl;
    delete _Brain;
    return;
}

Cat::Cat(const Cat &cpy) : Animal(cpy)
{
    std::cout << "Copy constructor called" << std::endl;
    this->_type = cpy._type;
    if (this->_Brain)
        delete _Brain;
    _Brain = new Brain(*cpy._Brain);
    return ;
}

Cat &Cat::operator=(const Cat &assign)
{
    std::cout << "Assignement operator called" << std::endl;
    if (&assign != this)
	{
		Animal::operator=(assign);
		delete _Brain;
        if (assign._Brain != NULL)
            _Brain = new Brain(*assign._Brain);
        else
            _Brain = NULL;
	}
    _type = assign._type;
    return (*this);
}

void    Cat::makeSound(void) const
{
    std::cout << "Cat inheritance say : Meow 😺" << std::endl;
}