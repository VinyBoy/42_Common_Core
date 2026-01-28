/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:36:58 by viny              #+#    #+#             */
/*   Updated: 2025/11/17 16:03:37 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Data.hpp"
#include "../includes/Serialize.hpp"

int main()
{
	Data test;
	test.id = 42;
	test.name = "test";

	std::cout << "Data adress before serialization :" << &test << std::endl;
	uintptr_t raw = Serializer::serialize(&test);
	std::cout << "Value of raw after serialization : " << raw << std::endl;
	Data *ptr = Serializer::deserialize(raw);

	std::cout << "\nOriginal pointer :" << &test << std::endl;
	std::cout << "Deserialized ptr : " << ptr << std::endl;

	if (ptr == &test)
		std::cout << "\nPointeur match." << std::endl;
	else
		std::cout << "\nPointers do not match." << std::endl;
	
	std::cout << "\nid : " << ptr->id << " name: " << ptr->name << std::endl;
	return (0);
}