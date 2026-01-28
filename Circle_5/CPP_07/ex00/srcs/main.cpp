/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:07:58 by viny              #+#    #+#             */
/*   Updated: 2025/11/23 17:59:08 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../includes/whatever.hpp"

int main(void)
{
	int	a = 2;
	int	b = 3;
	std::string s1 = "Hello";
	std::string s2 = "yo";
	
	std::cout << "\n\t--- Test swap int---\n" << std::endl;
	std::cout << "Before swap\n\n a =  " << a << " b =  " << b << "\n" << std::endl;
	::swap(a, b);
	std::cout << "After swap\n\n a =  " << a << " b =  " << b << std::endl;

	std::cout << "\n\t--- Test min ---\n" << std::endl;
	std::cout << "a = " << a << " b = " << b << std::endl;
	std::cout << "min is :" << ::min(a, b) << std::endl;

	std::cout << "\n\t--- Test max ---\n" << std::endl;
	std::cout << "a = " << a << " b = " << b << std::endl;
	std::cout << "max is :" << ::max(a, b) << std::endl;

	std::cout << "\n\t--- Test swap string---\n" << std::endl;
	std::cout << "Before swap\n\n s1 =  " << s1 << " s2 = " << s2 << "\n" << std::endl;
	::swap(s1, s2);
	std::cout << "After swap\n\n s1 =  " << s1 << " s2 = " << s2 << std::endl;

	std::cout << "\n\t--- Test min ---\n" << std::endl;
	std::cout << "s1 = " << s1 << " s2 = " << s2 << std::endl;
	std::cout << "min is :" << ::min(s1, s2) << std::endl;

	std::cout << "\n\t--- Test max ---\n" << std::endl;
	std::cout << "s1 = " << s1 << " s2 = " << s2 << std::endl;
	std::cout << "max is :" << ::max(s1, s2) << std::endl;
    return (0);
}