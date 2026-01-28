/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:46:55 by viny              #+#    #+#             */
/*   Updated: 2025/11/23 16:01:41 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../includes/whatever.hpp"

Whatever::Whatever(void) {}

Whatever::~Whatever(void) {}

Whatever::Whatever(Whatever const &cpy)
{    
    *this = cpy;
}


Whatever& Whatever::operator=(Whatever const & assign) {

	(void)assign;
    return (*this);
}
