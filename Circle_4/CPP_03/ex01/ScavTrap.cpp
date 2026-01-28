/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:21:49 by viny              #+#    #+#             */
/*   Updated: 2025/09/09 19:36:11 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ScavTrap.hpp"

//Forme Canonique
ScavTrap::ScavTrap(void) : ClapTrap("NoName")
{
    _Hit = 100;
    _Energy = 50;
    _Attack = 20;
    std::cout << "ScavTrap default constructor from : " << _name << std::endl;
    return ;
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name)
{
    _Hit = 100;
    _Energy = 50;
    _Attack = 20;
    std::cout << "ScavTrap constructor from : " << _name << std::endl;
    return ;
}

ScavTrap::~ScavTrap(void)
{
    std::cout << "ScavTrap destructor called from" << _name  << std::endl;
    return ;
}

ScavTrap::ScavTrap(ScavTrap const &cpy) : ClapTrap(cpy)
{
    std::cout << "ScavTrap Copy constructor called from [" << cpy._name << "]" << std::endl;
    return ;
}

//Surcharge <<
ScavTrap & ScavTrap::operator=(ScavTrap const &assign)
{
    std::cout << "ScavTrap assignement operator called" << std::endl;
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
void    ScavTrap::attack(const std::string &target)
{
    if (!isAlive(_Hit))
    {
        std::cout << "ScavTrap " << _name << " cannot attack: no hit points." << std::endl;
        return ;
    }
    if (!hasEnergy(_Energy))
    {
        std::cout << "ScavTrap " << _name << " cannot attack: no energy points." << std::endl;
        return ;
    }
    std::cout << "\nScavTrap : \n" << _name << " Jette une Big ⛏️ sauvage sur : " << target
        << ", causing : " << _Attack << " points of damage ! 🪫 \n" << std::endl;
    _Energy -= 1;
    return ;
}

void    ScavTrap::guardGate(void)
{
    std::cout << "ScaveTrap : " << _name << " is now in Gate keeper mode. ⛩️ 🚫\n" << std::endl;
    return ;
}
