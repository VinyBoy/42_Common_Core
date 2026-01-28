/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:16:14 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/08/31 17:22:44 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(int argc, char **argv)
{
    Zombie *newZombie = NULL;

    if (argc != 2 ) {
        std::cout << "Usage : ./Zombie \"name\"";
        return (1);
    }
    try { newZombie = new Zombie();}
    catch (const std::bad_alloc&)
    {
        std::cout << "bad alloc\n";
        return (1);
    }
    randomChump("Zombie of the Stack");
    if (!newZombie->SetName(argv[1])) {
        return (1);
    }
    newZombie->annonce();
    delete newZombie;
    return (0);
}
