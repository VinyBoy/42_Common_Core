/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:48:58 by viny              #+#    #+#             */
/*   Updated: 2025/11/27 15:27:34 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/easyfind.hpp"
#include <vector>
#include <list>
#include <string>

int	main(void)
{
	std::cout << "--- Test Vector int ---" << std::endl;
	std::vector<int> vector;
	vector.push_back(1);
	vector.push_back(2);
	vector.push_back(3);
	try
	{
		std::cout << "Found -> " << *EasyFind(vector, 2) << std::endl;
		std::cout << "Found -> " << *EasyFind(vector, 4) << std::endl;

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "\n--- Test list ---" << std::endl;
	int j = 1;
	std::list<int> lst;
	lst.push_back(1);
	lst.push_back(10);
	lst.push_back(100);
	lst.push_back(1000);
	lst.push_back(10000);
	lst.push_back(100000);
	lst.push_back(1000000);
	lst.push_back(10000000);
	lst.push_back(100000000);
	try
	{
		for (int i = 0; i < 10; i++)
		{
			std::cout << "Found -> " << *EasyFind(lst, j) << std::endl;
			j = j *10;
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << " after j = " << j << '\n';
	}
}