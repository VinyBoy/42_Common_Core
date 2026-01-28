/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:34:04 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/08/31 18:00:54 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(const std::string weapon) : _type(weapon) {
}

Weapon::~Weapon() {}

void    Weapon::setType(const std::string type)
{
    _type = type;
}

const   std::string&   Weapon::getType(void) const
{
    return (_type);
}