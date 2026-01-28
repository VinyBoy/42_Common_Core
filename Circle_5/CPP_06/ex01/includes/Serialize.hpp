/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serialize.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:37:11 by viny              #+#    #+#             */
/*   Updated: 2025/11/17 15:50:00 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../includes/Data.hpp"
#include <string>
#include <stdint.h>


class Serializer
{
	public :
		static uintptr_t serialize(Data *ptr);
		static Data *deserialize(uintptr_t raw);
	private :
		Serializer();
		~Serializer();
		Serializer(const Serializer &cpy);
		Serializer & operator=(const Serializer &assign);	
};