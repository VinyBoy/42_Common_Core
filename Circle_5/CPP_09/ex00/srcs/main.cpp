/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:37:02 by viny              #+#    #+#             */
/*   Updated: 2025/12/05 15:40:09 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage : ./btc input.txt" << std::endl;
		return (1);
	}
	try 
	{
		BitcoinExchange instanceBtc("data.csv");
		instanceBtc.parseFile(argv[1]);
	} catch (std::exception &e)
	{
		std::cout << "Error : " << e.what() << std::endl;
	}
	return (0);
}