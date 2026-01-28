/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:29:04 by viny              #+#    #+#             */
/*   Updated: 2025/08/29 17:17:00 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

const Harl::Entry Harl::Table[] =
{
    {"DEBUG", &Harl::debug},
    {"INFO", &Harl::info},
    {"WARNING", &Harl::warning},
    {"ERROR", &Harl::error}
};

void    Harl::complain(const std::string level)
{
    const   size_t N = sizeof(Table) / sizeof(Table[0]);
    //On parcour notre table pour trouver la string correspondante et appele 
    //la methode membre adequate
    for (size_t i = 0; i < N; i++)
    {
        //Si la string level == le nom attribue a la methode membre concerner
        if (level == Table[i].name)
        {
            //On declare une variable de type Action et on lui attribue notre
            //methode membre
            Action a;
            a = Table[i].fn;
            //On appelle avc this l'action de notre instance actuelle
            (this->*a)();
            return ;
        }
    }
}

void Harl::debug(void) {
    std::cout
        << "I love having extra bacon for my 7XL-double-cheese-"
           "triple-pickle-special-ketchup burger. I really do!"
        << std::endl;
}

void Harl::info(void) {
    std::cout
        << "I cannot believe adding extra bacon costs more money. "
           "You didn’t put enough bacon in my burger! If you did, "
           "I wouldn’t be asking for more!"
        << std::endl;
}

void Harl::warning(void) {
    std::cout
        << "I think I deserve to have some extra bacon for free. "
           "I’ve been coming for years, whereas you started working "
           "here just last month."
        << std::endl;
}

void Harl::error(void) {
    std::cout
        << "This is unacceptable! I want to speak to the manager now."
        << std::endl;
}