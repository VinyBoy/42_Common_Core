/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:04:36 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/08/21 21:20:55 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "HumanB.hpp"

HumanB::HumanB(const std::string name) : _name(name), _weapon(0) {};

HumanB::~HumanB() {};

void    HumanB::setWeapon(Weapon &type)
{
    _weapon = &type;
}

void HumanB::clearWeapon() { _weapon = 0; }

void    HumanB::attack(void)
{
    if (_weapon == 0 || _weapon->getType().empty())
        std::cout << _name << " has no weapon to attack with!" << std::endl;
    else
        std::cout << _name << " attacks with their " << _weapon->getType() << std::endl; 
}
