/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:51:32 by viny              #+#    #+#             */
/*   Updated: 2025/11/18 16:19:05 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Base.hpp"
#include "../includes/A.hpp"
#include "../includes/B.hpp"
#include "../includes/C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include <exception>

Base::~Base() {}

Base	*generate(void)
{
	int	random = rand() % 3;

	if (random == 0)
		return (new A);
	else if (random == 1)
		return (new B);
	else   
		return (new C);
}

void	identify(Base *p)
{
    if (p == NULL)
    {
        std::cout << "Unknown ptr" << std::endl;
        return;
    }
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
    else
        std::cout << "Unknown" << std::endl;
}

void	identify(Base &p)
{
    if (dynamic_cast<A*>(&p))
    {
        std::cout << "A" << std::endl;
        return;
    }
    if (dynamic_cast<B*>(&p))
    {
        std::cout << "B" << std::endl;
        return;
    }
    if (dynamic_cast<C*>(&p))
    {
        std::cout << "C" << std::endl;
        return;
    }
    std::cout << "Unknown" << std::endl;
}

