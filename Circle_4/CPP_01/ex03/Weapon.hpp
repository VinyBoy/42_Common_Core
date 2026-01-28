/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:21:28 by viny              #+#    #+#             */
/*   Updated: 2025/08/20 21:23:39 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>
#include <iomanip>
#include <string>

class Weapon {

	public :
		Weapon(const std::string weapon);
		~Weapon();
		const std::string& 	getType() const;
		void				setType(std::string type);

	private :
		std::string _type;
	
};

#endif