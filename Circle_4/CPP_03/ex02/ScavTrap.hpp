/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:22:19 by viny              #+#    #+#             */
/*   Updated: 2025/09/09 19:07:39 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAV_TRAP
#define SCAV_TRAP

#include <iostream>
#include "ClapTrap.hpp"
#include <string>

class  ScavTrap : public ClapTrap
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