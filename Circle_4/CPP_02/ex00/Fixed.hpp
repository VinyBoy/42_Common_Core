/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:22:19 by viny              #+#    #+#             */
/*   Updated: 2025/09/02 21:23:12 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {

public :

    Fixed(void);                               // Constructeur par defaut
    Fixed(int const n);             
    Fixed(Fixed const& src);                  // Construteur par copie
    ~Fixed(void);                              // Destructeur
    
    Fixed& operator=(Fixed const & rhs);      // Operateur d'assignation
    int     getRawBits(void) const;           //Getter
    void    setRawBits(int const raw);

private :

    int _Raw;
    static const int    _fractionalBits = 8;
};

//Surcharge chevron << redirection flux vers sortie standard 
std::ostream & operator<<(std::ostream &o, Fixed const &i);

#endif