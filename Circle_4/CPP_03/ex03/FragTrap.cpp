/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:21:49 by viny              #+#    #+#             */
/*   Updated: 2025/09/09 20:06:38 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "FragTrap.hpp"
#include "FragTrap.hpp"

//Forme Canonique
FragTrap::FragTrap(void) : ClapTrap("NoName")
{
    _Hit = 100;
    _Energy = 100;
    _Attack = 30;
    std::cout << "FragTrap default constructor from : " << _name << std::endl;
    return ;
}

FragTrap::FragTrap(const std::string &name) : ClapTrap(name)
{
    _Hit = 100;
    _Energy = 50;
    _Attack = 20;
    std::cout << "FragTrap constructor from : " << _name << std::endl;
    return ;
}

FragTrap::~FragTrap(void)
{
    std::cout << "FragTrap destructor called from" << _name  << std::endl;
    return ;
}

FragTrap::FragTrap(FragTrap const &cpy) : ClapTrap(cpy)
{
    std::cout << "FragTrap Copy constructor called from [" << cpy._name << "]" << std::endl;
    return ;
}

//Surcharge <<
FragTrap & FragTrap::operator=(FragTrap const &assign)
{
    std::cout << "FragTrap assignement operator called" << std::endl;
    if (&assign != this)
        ClapTrap::operator=(assign); 
    return (*this);
}

//Helpers
static bool isAlive(unsigned int hp)
{
    return (hp > 0);
}

static bool hasEnergy(unsigned int stamina)
{
    return (stamina > 0);
}

//Methode membre
void    FragTrap::attack(const std::string &target)
{
    if (!isAlive(_Hit))
    {
        std::cout << "FragTrap " << _name << " cannot attack: no hit points." << std::endl;
        return ;
    }
    if (!hasEnergy(_Energy))
    {
        std::cout << "FragTrap " << _name << " cannot attack: no energy points." << std::endl;
        return ;
    }
    std::cout << "\nFragTrap : \n" << _name << " Jette une innocente 🪓 sur : " << target
        << ", causing : " << _Attack << " points of damage ! 🪫 \n" << std::endl;
    _Energy -= 1;
    return ;
}

void    FragTrap::highFivesGuys(void)
{
    std::cout << "FragTrap : " << _name << " Yeah High-fives ✋ \n" << std::endl;
    return ;
}
