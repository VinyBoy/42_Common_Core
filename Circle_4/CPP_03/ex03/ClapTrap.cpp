/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:21:49 by viny              #+#    #+#             */
/*   Updated: 2025/09/09 20:11:23 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ClapTrap.hpp"

//Forme Canonique
ClapTrap::ClapTrap(void) : _name(), _Hit(10), _Energy(10), _Attack(0)
{
    std::cout << "Clap Trap default constructor called for[" << _name << "]" << std::endl;
    return ;
}

ClapTrap::ClapTrap(const std::string &name) : _name(name), _Hit(10), _Energy(10), _Attack(0)
{
    std::cout << "Clap Trap default constructor called for [" << _name << "]" << std::endl;
    return ;
}

ClapTrap::~ClapTrap(void)
{
    std::cout << "ClapTrap destructor called from" << _name  << std::endl;
    return ;
}

ClapTrap::ClapTrap(ClapTrap const &cpy) : _name(cpy._name), _Hit(cpy._Hit), _Energy(cpy._Energy), _Attack(cpy._Attack)
{
    std::cout << "ClapTrap Copy constructor called from [" << cpy._name << "]" << std::endl;
    *this = cpy;
    return ;
}

//Accesseurs
std::string ClapTrap::getName(void) const
{
    return (_name);
}

void    ClapTrap::setName(std::string const &name)
{
    _name = name;
}

unsigned int ClapTrap::getHitPoints() const
{
    return _Hit;
}

unsigned int ClapTrap::getEnergyPoints() const
{
    return _Energy;
}

unsigned int ClapTrap::getAttackDamage() const
{
    return _Attack;
}

void ClapTrap::setAttackDamage(unsigned int amount)
{
    _Attack = amount;
}


//Surcharge <<
ClapTrap & ClapTrap::operator=(ClapTrap const &assign)
{
    std::cout << "ClapTrap assignement operator called" << std::endl;
    if (&assign != this)
    {
        _name   = assign._name;
        _Hit    = assign._Hit;
        _Energy = assign._Energy;
        _Attack = assign._Attack;
    }
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
void    ClapTrap::attack(const std::string &target)
{
    if (!isAlive(_Hit))
    {
        std::cout << "ClapTrap " << _name << " cannot attack: no hit points." << std::endl;
        return ;
    }
    if (!hasEnergy(_Energy))
    {
        std::cout << "ClapTrap " << _name << " cannot attack: no energy points." << std::endl;
        return ;
    }
    std::cout << "\nClapTrap : \n" << _name << " Jette un jeune 🔪 sauvage sur : " << target
        << ", causing : " << _Attack << " points of damage ! 🪫 \n" << std::endl;
    _Energy -= 1;
}

void    ClapTrap::takeDamage(unsigned int amount)
{
    if (!isAlive(_Hit))
    {
        std::cout << "ClapTrap\n" << _name << " is already at 0 HP." << std::endl;
        return ; 
    }
    if (amount >= static_cast<unsigned int>(_Hit))
        _Hit = 0;
    else
        _Hit -= amount;
    std::cout << "ClapTrap : \n" << _name << " take : " << amount << " of dammage 🪫\n"
        << std::endl;
    std::cout << "Hit point of " << _name << " : " << _Hit << " 🔋\n" << std::endl;
}

void    ClapTrap::beRepaired(unsigned int amount)
{
    std::cout << "ClapTrap : \n" << _name << " Repaired : " << amount << " of Hit point"
        << std::endl;
    _Hit += amount;
    std::cout << "Hit point of " << _name << " : " << _Hit << " 🔋\n" << std::endl;
    _Energy -= 1;
}


