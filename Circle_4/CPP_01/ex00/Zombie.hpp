/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:24:06 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/08/13 19:54:09 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP
#include <iostream>
#include <iomanip>
#include <string>

class Zombie {

    public :
    
    Zombie(void);
    ~Zombie(void);

    void    annonce(void);

    //Getter
    std::string GetName()const;
    //Setter
    bool SetName(const std::string &n);

    private :
    
    std::string _name;
};

void    randomChump(std::string name);
Zombie* newZombie(std::string name);

#endif