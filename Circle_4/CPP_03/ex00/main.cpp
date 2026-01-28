/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:07:58 by viny              #+#    #+#             */
/*   Updated: 2025/09/10 15:09:38 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ClapTrap.hpp"

int main(void)
{
    ClapTrap A("BillyLeBicraveurDeNoodle 👺🍜");
    ClapTrap B("JeuneIencli 👶");
    ClapTrap C("DenisLaMalice 🥷");

    A.attack (B.getName());
    B.takeDamage(20);
    B.attack(A.getName());
    A.attack (C.getName());
    C.takeDamage(0);
    
    return (0);
}