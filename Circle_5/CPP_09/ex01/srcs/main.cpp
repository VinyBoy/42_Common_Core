/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:37:02 by viny              #+#    #+#             */
/*   Updated: 2025/12/08 14:23:57 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error : Usage is -> ./RPN \"Operation\"" << std::endl;
		return (1);
	}
	try 
	{
		std::string arg = argv[1];
		Rpn rpn(arg);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}