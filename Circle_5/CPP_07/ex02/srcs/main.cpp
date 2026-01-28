/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:07:58 by viny              #+#    #+#             */
/*   Updated: 2025/11/24 00:07:23 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "../includes/Array.hpp"

template <typename T> 
void printArray(const Array<T> &array)
{
	for (unsigned int i = 0; i < array.getSize(); i++)
		std::cout << array[i] << " ";
	std::cout << std::endl;
}

int main(void)
{
	std::cout << "\n--- Test Constructeur par default ---" << std::endl;
	Array<int> empty;
	std::cout << "Array size = " << empty.getSize() << std::endl;

	std::cout << "\n--- Test Constructeur avec n ---" << std::endl;
	Array<int> nb(5);
	for (unsigned int i = 0; i < nb.getSize(); i++)
		nb[i] = i;
	printArray(nb);
	
	std::cout << "\n--- Test deep copy ---" << std::endl;
	Array<int> cpy(nb);
	printArray(cpy);

	std::cout <<  "\n--- Test Modif --- " << std::endl;
	nb[0] = 8;
	printArray(nb);
	printArray(cpy);
	
	std::cout << "\n--- Test affectation ---" << std::endl;
	Array<int> assign;
	assign = nb;
	printArray(assign);
	
	std::cout << "\n--- Test acces const ---" << std::endl;
	const Array<int> constArray(nb);
	std::cout << "const array[2] = " << constArray[0] << std::endl;

	std::cout << "\n--- Test exception ---" << std::endl;
	try
	{
		std::cout << nb[100] << std::endl;
	} catch( std::exception &e) {
		std::cout << "Error : " << e.what() << std::endl;
	}
	
	std::cout << "\n--- Test string ---" << std::endl;
	Array<std::string> str(3);
	str[0] = "Hello";
	str[1] = "ca va";
	str[2] = "Oui et toi bg";
	printArray(str);

	return (0);
 	
}