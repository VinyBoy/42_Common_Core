/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:04:39 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/08/20 21:49:39 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"
#include "HumanA.hpp"

HumanA::HumanA(const std::string name, Weapon &type) : _name(name), _weapon(type) {}

HumanA::~HumanA() {}

void    HumanA::attack(void)
{
    std::cout << _name << " attacks with their " << _weapon.getType() << std::endl; 
}

void    HumanA::setType(const std::string name, Weapon typeWeapon)
{
    std::string weapon;

    weapon = typeWeapon.getType();
    _weapon = weapon;
    _name = name;
}