/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:22:19 by viny              #+#    #+#             */
/*   Updated: 2025/09/10 11:13:30 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAV_TRAP
#define SCAV_TRAP

#include <iostream>
#include "ClapTrap.hpp"
#include <string>

class  ScavTrap : virtual public ClapTrap
{
    public :
        ScavTrap(void);
        ScavTrap(const std::string &name);
        ~ScavTrap(void);
        ScavTrap(const ScavTrap &cpy);
        ScavTrap &operator=(const ScavTrap &assign);
    
        void    attack(const std::string &target);
        void    guardGate();
};

#endif