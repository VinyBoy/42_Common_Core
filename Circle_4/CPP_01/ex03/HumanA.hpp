/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:04:42 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/08/20 21:47:08 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMAN_A
#define HUMAN_A

#include "Weapon.hpp"


class HumanA{

    public :
    
        HumanA(const std::string name, Weapon &type);
        ~HumanA(void);
        void    setType(const std::string name, Weapon club);
        void    attack();
        
    private :
        std::string _name;
        Weapon &_weapon;
};

#endif