/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:25:51 by viny              #+#    #+#             */
/*   Updated: 2025/08/29 17:17:25 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
#define HARL_HPP

#include <string>

class Harl
{
    public :
    
        void complain(std::string level);

    private :
    
        void debug(void);
        void info(void);
        void warning(void);
        void error(void);

        //pointeur vers methode membre
        typedef void(Harl::*Action)(void);
        //Table ou on va stockee les fonctions
        struct Entry
        {
            const char *name;
            Action      fn;
        };
        //Table de dispatch
        static const Entry Table[];
        
};


#endif