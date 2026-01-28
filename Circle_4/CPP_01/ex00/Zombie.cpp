/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:34:21 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/08/31 17:22:17 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie() : _name() {
    std::cout << "Constructor from class Zombie is called" << std::endl;
}

Zombie::~Zombie() {
    std::cout << "Destructor from " << _name << " class Zombie is called" << std::endl;
}

void    Zombie::annonce(void) {
    
    std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

std::string    Zombie::GetName() const {

    return (_name);
}

bool    Zombie::SetName(const std::string &n)
{
    if (n.empty()) {
        std::cout << "Name is empty" << std::endl;
        return (false);
    }
    _name = n;
    return (true);
}
