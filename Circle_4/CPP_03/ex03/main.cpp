/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:07:58 by viny              #+#    #+#             */
/*   Updated: 2025/09/10 11:50:40 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"

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

    std::cout << "\n\t\t-------------Fragtrap-------------\n" << std::endl;
    
    FragTrap G("Kurapika 🔴🔴");
    std::cout << "HP=" << G.getHitPoints() << " EP=" << G.getEnergyPoints()
    << " AD=" << G.getAttackDamage() << "\n\n";
    FragTrap H("Leolio 🥼");
    std::cout << "HP=" << H.getHitPoints() << " EP=" << H.getEnergyPoints()
    << " AD=" << H.getAttackDamage() << "\n\n";
    G.attack(H.getName());
    std::cout << G.getName() << " Energy point :" << G.getEnergyPoints() << std::endl;
    H.takeDamage(20);
    H.beRepaired(20);
    std::cout << H.getName() << " Energy point :" << H.getEnergyPoints() << "\n" << std::endl;
    H.highFivesGuys();
    G.highFivesGuys();
    
	std::cout << "\n\t\t-------------DiamondTrap-------------\n" << std::endl;
	DiamondTrap I ("Joey Star 🧥");
	DiamondTrap J ("Dio Brando 🗿");
	I.attack(J.getName());
	J.takeDamage(30);
	J.getHitPoints();
	I.whoAmI();
	J.whoAmI();
	
    
    return (0);
}