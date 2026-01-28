/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:43:42 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/09/11 16:08:20 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain(void)
{
    std::cout << "Brain default constructor called" << std::endl;
    return ;
}

Brain::~Brain(void)
{
    std::cout << "Brain destructor called" << std::endl;
    return;
}

Brain::Brain(const Brain &cpy) : Animal(cpy)
{
    std::cout << "Copy constructor called" << std::endl;
	for (int i = 0; i < 100; i++)
        _ideas[i] = cpy._ideas[i];
    this->_type = cpy._type;
    return ;
}

Brain &Brain::operator=(const Brain &assign)
{
    std::cout << "Assignement operator called" << std::endl;
    if (&assign != this)
        _type = assign._type;
    return (*this);
}

void    Brain::makeSound(void) const
{
    std::cout << "Brain inheritance say : TheTingGoSkraaaa" << std::endl;
}

std::string Brain::getIdeas(int i) const
{
	if (i < 0 || i >= 100)
        return "Error: Wrong index";
    else if (_ideas[i].empty())
        return "Error: No idea at this index";
	else
        return (_ideas[i]);
}


void	Brain::setIdeas(const std::string &id, int idx)
{
    if (idx < 0 || idx > 100) {
        std::cerr << "Error: out of range" << std::endl;
        return ;
    }
	_ideas[idx] = id;
}