/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:04:32 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/08/21 15:40:22 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMAN_B
#define HUMAN_B

#include "HumanA.hpp"
#include "Weapon.hpp"

class HumanB
{
    public :
    
        HumanB(const std::string name);
        ~HumanB();
        void    setWeapon(Weapon &type);
        void    attack();
        void    clearWeapon();
        

    private :
        std::string _name;
        Weapon *_weapon;
    
};

#endif