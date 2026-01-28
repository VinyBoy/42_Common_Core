/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:43:42 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/09/15 13:46:32 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat(void)
{
    std::cout << "WrongCat default destructor called" << std::endl;
    return ;
}

WrongCat::~WrongCat(void)
{
    std::cout << "WrongCat destructor called" << std::endl;
    return;
}

WrongCat::WrongCat(const WrongCat & cpy) : WrongAnimal(cpy)
{
    std::cout << "Copy constructor called" << std::endl;
    this->_type = cpy._type;
    return ;
}

WrongCat &WrongCat::operator=(const WrongCat &assign)
{
    std::cout << "Assignement operator called" << std::endl;
    if (&assign != this)
        _type = assign._type;
    return (*this);
}

void    WrongCat::makeSound(void) const
{
    std::cout << "WrongCat inheritance say : Meow" << std::endl;
}