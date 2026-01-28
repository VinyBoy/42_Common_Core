/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:38:40 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/10/14 18:09:34 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>
#include "Animal.hpp"

class Brain : public Animal
{
    public :
        Brain();
        Brain(const Brain & cpy);
        Brain & operator=(const Brain &assign);
        virtual ~Brain();
        virtual void makeSound() const;
		void	setIdeas(const std::string &id, int idx);
		std::string getIdeas(int i) const;
    private :
        std::string _ideas[100];
};

#endif