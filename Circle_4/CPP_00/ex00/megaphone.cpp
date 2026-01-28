/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:59:01 by viny              #+#    #+#             */
/*   Updated: 2025/07/19 23:49:38 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cctype>

std::string    to_uppercase(std::string &str)
{
    std::string new_str;

    new_str = str;
    for (size_t i = 0; i < str.length(); ++i)
        new_str[i] = std::toupper(str[i]);
    return (new_str);
}

int main(int argc, char **argv)
{
    if (argc <= 1)
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
    else
    {
        for(int i = 1; i < argc; i++)
        {
            std::string temp_argv = argv[i];
            std::cout << to_uppercase(temp_argv);
        }
        std::cout << std::endl;
    }
    return (0);
}
