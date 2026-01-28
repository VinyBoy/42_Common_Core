/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:36:58 by viny              #+#    #+#             */
/*   Updated: 2025/11/18 16:07:18 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Base.hpp"
#include <iostream>
#include <cstdlib>

int main(void)
{
    srand(time(NULL));
	std::cout << " Test generate() / identify()\n\n";

    for (int i = 1; i <= 5; ++i)
    {
        std::cout << "[Iteration " << i << "]\n";
        Base *ptr = generate();
        std::cout << "pointer address: " << ptr << "\n";

        std::cout << "identify(ptr): ";
        identify(ptr);

        std::cout << "identify(ref): ";
        identify(*ptr);

        delete ptr;
        std::cout << "(deleted)\n\n";
    }

    std::cout << "Test identify(NULL) : ";
    identify(static_cast<Base*>(NULL));
    return (0);
}