/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:07:58 by viny              #+#    #+#             */
/*   Updated: 2025/09/09 19:33:43 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main(void)
{
    std::cout << "\n\t\t-------------Claptrap-------------\n" << std::endl;
    
    ClapTrap A("BillyLeBicraveurDeNoodle 👺🍜");
    ClapTrap B("JeuneIencli 👶");
    ClapTrap C("DenisLaMalice 👱🏼");

    A.attack (B.getName());
    B.takeDamage(5);
    B.attack(A.getName());
    A.attack (C.getName());
    C.takeDamage(0);
    std::cout << "\n\t\t-------------Scavtrap-------------\n" << std::endl;
    
    ScavTrap D("Bender 🤖");
    std::cout << "HP=" << D.getHitPoints() << " EP=" << D.getEnergyPoints()
        << " AD=" << D.getAttackDamage() << "\n\n";
    ScavTrap E("Brice 🏄");
    ScavTrap F("Jackie Chan 👲");

    D.attack(E.getName());
    E.takeDamage(100);
    E.attack(D.getName());
    E.beRepaired(10);
    E.attack(D.getName());
    D.takeDamage(10);
    F.guardGate();
    return (0);
}