/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:27:56 by viny              #+#    #+#             */
/*   Updated: 2025/08/15 22:15:47 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(int argc, char **argv)
{
	Zombie *ZombieHorde;
	int		nb;

	if (argc != 3)
		return (std::cout << "Usage : ./Zombie \"Nb of Zombie\"" "\"name\"" << std::endl, 1);
	nb = atoi(argv[1]);
	if (nb <= 0 || nb > INT_MAX)
		return (std::cout << "Bad number of Zombie pls enter between 1 & INT MAX ty" << std::endl, 1);
	ZombieHorde = zombieHorde(nb, argv[2]);
	if (!ZombieHorde)
		return (1);
	delete[] ZombieHorde;
	return (0);
}