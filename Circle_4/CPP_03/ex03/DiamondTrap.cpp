/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:21:49 by viny              #+#    #+#             */
/*   Updated: 2025/09/10 11:51:37 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"
#include <iostream>

DiamondTrap::DiamondTrap(void)
: ClapTrap("no clap name")
, ScavTrap()
, FragTrap()
, _name("no name")
{
	_Hit = 100;
    _Energy = 50;
    _Attack = 30;
    std::cout << "DiamondTrap default constructor from : " << _name << std::endl;
    return ;
}

DiamondTrap::DiamondTrap(const std::string &name)
: ClapTrap(name + "_clap name")
, ScavTrap(name)
, FragTrap(name)
, _name(name)
{
	_Hit = 100;
    _Energy = 50;
    _Attack = 30;
    std::cout << "DiamondTrap constructor from : " << _name << std::endl;
    return ;
}

DiamondTrap::DiamondTrap(const DiamondTrap& cpy)
: ClapTrap(cpy)
, ScavTrap(cpy)
, FragTrap(cpy)
, _name(cpy._name)
{
    std::cout << "DiamondTrap copy constructor from " << cpy._name << std::endl;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& assign)
{
    if (this != &assign)
	{
        ClapTrap::operator=(assign); // copie la partie base (virtual base unique)
        ScavTrap::operator=(assign);
        FragTrap::operator=(assign);
        _name = assign._name;
    }
    std::cout << "DiamondTrap copy assigned from " << assign._name << std::endl;
    return (*this);
}

DiamondTrap::~DiamondTrap()
{
    std::cout << "DiamondTrap destructor called " << _name << std::endl;
}

void DiamondTrap::attack(const std::string& target)
{
    // Le sujet veut l'attaque de ScavTrap
    ScavTrap::attack(target);
}

void DiamondTrap::whoAmI()
{
    // Attention: _name (DiamondTrap) SHADOW l'attribut ClapTrap::_name
    // On accède explicitement à celui de ClapTrap via qualification :
    std::cout << "DiamondTrap whoAmI -> my name : " << _name
              << ", ClapTrap name: " << this->ClapTrap::_name << "\n" << std::endl;
}