/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:25:06 by viny              #+#    #+#             */
/*   Updated: 2025/08/29 19:14:36 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

static int  recover_index(const std::string &level)
{
    const char *name[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    for (size_t i = 0; i < 4; i++)
    {
        if (level == name[i])
            return (i);
    }
    return (-1);
}
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout <<  "Usage : ./Harl_filter "
            "\"DEBUG / INFO / WARNING / ERROR\"" << "\n";
        return (1);
    }
    
    std::string level = argv[1];
    const int index = recover_index(level);
    Harl h;
    
    switch (index)
    {
        case 0:
            std::cout << "[ DEBUG ]" << "\n";
            h.complain("DEBUG");
            /* fall through */
        case 1:
            std::cout << "[ INFO ]" << "\n";
            h.complain("INFO");
            /* fall through */
        case 2:
            std::cout << "[ WARNING ]" << "\n";
            h.complain("WARNING");
            /* fall through */
        case 3:
            std::cout << "[ ERROR ]" << "\n";
            h.complain("ERROR");
            break ;
        default :
            std::cout << "Error you must use : DEBUG / INFO / WARNING / ERROR" << std::endl;
    }
    return(0);
}