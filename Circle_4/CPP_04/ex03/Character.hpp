/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:07:12 by viny              #+#    #+#             */
/*   Updated: 2025/10/11 17:12:16 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTERE_HPP
#define CHARACTERE_HPP

#include "ICharacter.hpp"
#include "AMateria.hpp"
#include <string>

class Character : public ICharacter
{
	private :
		std::string _name;
		AMateria *_inventory[4];
	
	public :
		Character();
		Character(std::string const &name);
		Character(const Character &cpy);
		Character &operator=(const Character &assign);
		virtual ~Character();

		virtual std::string const & getName() const;
		virtual void equip(AMateria *m);
		virtual void unequip(int idx);
		virtual void use(int idx, ICharacter &target);
};

#endif
