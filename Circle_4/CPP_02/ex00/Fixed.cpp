/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:21:49 by viny              #+#    #+#             */
/*   Updated: 2025/09/02 21:25:02 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Fixed.hpp"

Fixed::Fixed(void) : _Raw(0) {
    
    std::cout << "Default Constructor called" << std::endl;
    return ;
}

Fixed::Fixed(int const n) : _Raw(n) {
    
    std::cout << "Parametric Constructor called" << std::endl;
    return ;
}

Fixed::Fixed(Fixed const &src) {
    
    std::cout << "Copy constructor called" << std::endl;
    *this = src;
    return ;
}

Fixed::~Fixed(void) {

    std::cout << "Destructor called" << std::endl;
    return ;
}

int Fixed::getRawBits(void) const {

    std::cout << "getRawBits member function called" << std::endl;
    return (_Raw);    
}

void    Fixed::setRawBits(int const raw) {

    _Raw = raw;
}

Fixed& Fixed::operator=(Fixed const & rhs) {
    
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &rhs)
        this->_Raw = rhs.getRawBits();
    return (*this);
}

std::ostream & operator<<(std::ostream &o, Fixed const &i) {
    
    o << "The value of _foo is : " << i.getRawBits();

    return (o);
}