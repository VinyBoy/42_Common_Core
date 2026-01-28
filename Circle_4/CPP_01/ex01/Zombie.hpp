/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:27:52 by viny              #+#    #+#             */
/*   Updated: 2025/08/15 22:04:53 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <limits.h>

class Zombie {
	
	private :
		std::string _name;
		
	public :
		void	annonce(void);
		bool	setName(std::string const & n);
	
};

Zombie* zombieHorde(int N, std::string name);

#endif