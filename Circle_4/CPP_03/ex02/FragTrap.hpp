/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:22:19 by viny              #+#    #+#             */
/*   Updated: 2025/09/09 19:53:53 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAG_TRAP
#define FRAG_TRAP

#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include <string>

class  FragTrap : public ClapTrap
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