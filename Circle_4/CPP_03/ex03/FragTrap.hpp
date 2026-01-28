/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:22:19 by viny              #+#    #+#             */
/*   Updated: 2025/09/10 11:13:46 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAG_TRAP
#define FRAG_TRAP

#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include <string>

class  FragTrap : virtual public ClapTrap
{
    public :
        FragTrap(void);
        FragTrap(const std::string &name);
        ~FragTrap(void);
        FragTrap(const FragTrap &cpy);
        FragTrap &operator=(const FragTrap &assign);
    
        void    attack(const std::string &target);
        void    highFivesGuys(void);
};

#endif