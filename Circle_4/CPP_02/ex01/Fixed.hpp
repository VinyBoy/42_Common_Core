/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:22:19 by viny              #+#    #+#             */
/*   Updated: 2025/09/02 21:45:37 by viny             ###   ########.fr       */
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

private :

    int _Raw;
    static const int    _fractionalBits = 8;
};

//Surcharge chevron << redirection flux vers sortie standard 
std::ostream & operator<<(std::ostream &o, Fixed const &i);

#endif