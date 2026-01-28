/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:50:50 by viny              #+#    #+#             */
/*   Updated: 2025/10/11 17:04:10 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
#define CURE_HPP

#include "AMateria.hpp"
#include "ICharacter.hpp"
#include <iostream>

class Cure : public AMateria
{
	public :
	Cure();
	Cure(const Cure &cpy);
	Cure &operator=(const Cure &assign);
	virtual ~Cure();
	
	virtual AMateria * clone() const;
	virtual void use(ICharacter & target);

	private :
		
};

#endif