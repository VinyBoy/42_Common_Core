/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:22:19 by viny              #+#    #+#             */
/*   Updated: 2025/09/09 18:11:14 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAP_TRAP
#define CLAP_TRAP

#include <iostream>
#include <string>

class ClapTrap
{
    public :
        ClapTrap( );
        ClapTrap(const std::string &name);
        ClapTrap(ClapTrap const &cpy);
        ClapTrap &operator=(ClapTrap const &assign);
        ~ClapTrap();

        std::string getName(void) const;
        void    setName(std::string const &name);

        void    attack(const std::string &target);
        void    takeDamage(unsigned int amount);
        void    beRepaired(unsigned int amount);

    private :
        std::string _name;
        int _Hit;
        int _Energy;
        int _Attack;
    
};

#endif