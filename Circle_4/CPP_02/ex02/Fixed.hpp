/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:22:19 by viny              #+#    #+#             */
/*   Updated: 2025/09/03 17:10:59 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {

public :

    Fixed(void);                               // Constructeur par defaut
    Fixed(Fixed const& src);                  // Construteur par copie
    Fixed& operator=(Fixed const & rhs);      // Operateur d'assignation
    ~Fixed(void);                              // Destructeur

    Fixed(int const n);
    Fixed(float const n);
    float toFloat(void) const;
    int   toInt(void) const;

    int     getRawBits(void) const;           //Getter
    void    setRawBits(int const raw);

    /*Comparaison*/
    bool operator>(Fixed const& rhs) const;
    bool operator<(Fixed const& rhs) const;
    bool operator>=(Fixed const& rhs) const;
    bool operator<=(Fixed const& rhs) const;
    bool operator==(Fixed const& rhs) const;
    bool operator!=(Fixed const& rhs) const;

    /*Arithmetic*/
    Fixed   operator+(Fixed const & rhs) const;
    Fixed   operator-(Fixed const & rhs) const;
    Fixed   operator*(Fixed const & rhs) const;
    Fixed   operator/(Fixed const & rhs) const;

    /*Increment / decrement*/
    Fixed & operator++();
    Fixed operator++(int);
    Fixed & operator--();
    Fixed operator--(int);

    /*Min / Max*/
    static Fixed& min(Fixed& a, Fixed& b);
    static const Fixed& min(const Fixed& a, const Fixed& b);
    static Fixed& max(Fixed& a, Fixed& b);
    static const Fixed& max(const Fixed& a, const Fixed& b);

private :

    int _Raw;
    static const int    _fractionalBits = 8;
};

//Surcharge chevron << redirection flux vers sortie standard 
std::ostream & operator<<(std::ostream &o, Fixed const &i);

#endif