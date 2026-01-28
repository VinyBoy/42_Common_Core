/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:53:16 by viny              #+#    #+#             */
/*   Updated: 2025/10/13 17:28:26 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <iostream>

class ICharacter;

class AMateria
{
	protected:
		std::string _type;
		
	public:
		AMateria(void);
		virtual ~AMateria(void);
		AMateria(const AMateria &cpy);
		AMateria & operator=(const AMateria & assign);
	
		AMateria(std::string const & type);
		std::string const & getType() const;
				
		virtual AMateria* clone() const = 0;
		virtual void use(ICharacter& target);
};

#endif