/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:21:49 by viny              #+#    #+#             */
/*   Updated: 2025/09/04 17:12:51 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cmath>

#include "Fixed.hpp"

/*                  Forme canonique                 */

//Constructeur
Fixed::Fixed(void) : _Raw(0) {
    
    std::cout << "Default Constructor called" << std::endl;
    return ;
}

//Constructeur de copie
Fixed::Fixed(Fixed const &src) {
    
    std::cout << "Copy constructor called" << std::endl;
    *this = src;
    return ;
}

//Operateur d'assignation
Fixed& Fixed::operator=(Fixed const & rhs) {
    
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &rhs)
    this->_Raw = rhs.getRawBits();
    return (*this);
}

//Destructeur
Fixed::~Fixed(void) {

    std::cout << "Destructor called" << std::endl;
    return ;
}

std::ostream & operator<<(std::ostream &o, Fixed const &i) {
    
    o << i.toFloat();
    return (o);
    
}

/*                      Accesseurs                      */


//Getteur
int Fixed::getRawBits(void) const {
    
    std::cout << "getRawBits member function called" << std::endl;
    return (_Raw);    
}

//Setter
void    Fixed::setRawBits(int const raw) {
    
    _Raw = raw;
}

/*                      Conversion en virgule fixe                          */

//Constructeur en Int
Fixed::Fixed(int const n) : _Raw(n)
{
    std::cout << "Int constructor called" << std::endl;
    _Raw = n << 8;
    return ;
}

//Constructeur en float
Fixed::Fixed(float const n)
{
    std::cout << "Float constructor called" << std::endl;
    _Raw = roundf(n * (1 << _fractionalBits));
    return ;
}

/*                      Conversion de virgule fixe a entier                     */

//Conversion virgule fixe en float
float Fixed::toFloat(void) const {

    return ((float)_Raw / (1 << _fractionalBits));
}

//Convertion virgule fixe en int
int Fixed::toInt(void) const {

    return (_Raw >> _fractionalBits);
}

/*              Comparaisons            */

bool Fixed::operator>(Fixed const& rhs) const
{
    return (this->_Raw > rhs._Raw);
}

bool Fixed::operator<(Fixed const& rhs) const
{
    return (this->_Raw < rhs._Raw);
}

bool Fixed::operator>=(Fixed const& rhs) const
{
    return (this->_Raw >= rhs._Raw);
}

bool Fixed::operator<=(Fixed const& rhs) const
{
    return (this->_Raw <= rhs._Raw);
}

bool Fixed::operator==(Fixed const& rhs) const
{
    return (this->_Raw == rhs._Raw);
}

bool Fixed::operator!=(Fixed const& rhs) const
{
    return (this->_Raw != rhs._Raw);
}

/*              Arithmetic                  */

Fixed   Fixed::operator+(Fixed const & rhs) const
{
    return (Fixed(this->toFloat() + rhs.toFloat()));
}

Fixed   Fixed::operator-(Fixed const & rhs) const
{
    return (Fixed(this->toFloat() - rhs.toFloat()));
}

Fixed   Fixed::operator*(Fixed const & rhs) const
{
    return (Fixed(this->toFloat() * rhs.toFloat()));
}

Fixed   Fixed::operator/(Fixed const & rhs) const
{
    return (Fixed(this->toFloat() / rhs.toFloat()));
}

/*                  Pre / Post increment            */
Fixed&  Fixed::operator++()
{
    _Raw++;
    return (*this);
}

Fixed   Fixed::operator++(int)
{
    Fixed tmp(*this);
    _Raw++;
    return (tmp);
}

Fixed&  Fixed::operator--()
{
    _Raw--;
    return (*this);
}
    
Fixed   Fixed::operator--(int)
{
    Fixed tmp(*this);
    _Raw--;
    return (tmp);
}

Fixed& Fixed::min(Fixed& a, Fixed& b)
{ 
    return (a < b) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b)
{
    return (a < b) ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b)
{
    return (a > b) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b)
{
    return (a > b) ? a : b;
}
