/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:53:32 by viny              #+#    #+#             */
/*   Updated: 2025/10/11 16:58:58 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
#define ICE_HPP

#include "AMateria.hpp"

class Ice : public AMateria
{
	public :
	Ice();
	Ice(const Ice &cpy);
	Ice &operator=(const Ice &assign);
	virtual ~Ice();

	virtual AMateria *clone() const	;
	virtual void use(ICharacter &target);
};

#endif