/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:27:28 by viny              #+#    #+#             */
/*   Updated: 2025/08/21 21:30:26 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <new>

Zombie* zombieHorde(int N, std::string name)
{
	Zombie	*new_Zombie;
	try {
		new_Zombie = new Zombie[N];
	} catch (const std::bad_alloc&){
		return (std::cout << "Error : bad alloc.\n", (Zombie*)NULL);
	}
	for (int i = 0; i < N; i++)
	{
		if (!new_Zombie[i].setName(name)) {
			delete[] new_Zombie;
			return (NULL); }
		new_Zombie[i].annonce();
	}
	return (new_Zombie);
}