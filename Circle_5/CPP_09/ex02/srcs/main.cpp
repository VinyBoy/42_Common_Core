/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:01:52 by viny              #+#    #+#             */
/*   Updated: 2025/12/21 18:52:41 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

static std::string convertDoubleArrayInString(int argc, char **argv)
{
	std::string newString;
	for (int i = 1; i < argc; i++)
	{
		newString += " ";
		newString += argv[i];
	}
	return(newString);
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error : Usage -> ./PmergeMe numbers to sort " << std::endl;
		return (1);
	}
	try
	{
		PmergeMe<std::vector<int> > objVec(convertDoubleArrayInString(argc, argv));
		clock_t start_vec = clock();
		objVec.run();
		clock_t end_vec = clock();
		unsigned long micros_vec = (end_vec -  start_vec) * 1000000UL / CLOCKS_PER_SEC;
		
		PmergeMe<std::deque<int> > objDeq(convertDoubleArrayInString(argc, argv));
		clock_t start_deque = clock();
		objDeq.run();
		clock_t end_deque = clock();
		unsigned long micros_deque = (end_deque -  start_deque) * 1000000UL / CLOCKS_PER_SEC;
		
		std::cout << "Time to process a range of " << objVec.getNbOfArg() << " elements with std::vector : " << micros_vec << " us" << std::endl; 
		std::cout << "Time to process a range of " << objDeq.getNbOfArg() << " elements with std::deque : "<< micros_deque << " us" << std::endl; 

	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}