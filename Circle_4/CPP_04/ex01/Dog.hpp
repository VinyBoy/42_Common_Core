/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:39:21 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/09/15 14:53:50 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
#define DOG_HPP

#include <iostream>
#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
    public :
        Dog();
        Dog(const Dog & cpy);
        Dog & operator=(const Dog &assign);
        virtual ~Dog();
        virtual void makeSound() const;
		Brain* getBrain() const; 
    private :
        Brain   *_Brain;
};

#endif
