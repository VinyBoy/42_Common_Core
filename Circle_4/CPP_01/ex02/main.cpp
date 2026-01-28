/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:05:21 by viny              #+#    #+#             */
/*   Updated: 2025/08/20 16:26:33 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <iomanip>

int main(void)
{
	std::string temp;
	std::string* stringPTR;
	std::string& stringREF = temp;

	temp = "HI THIS IS BRAIN";
	stringPTR = &temp;

	std::cout << "Memory adress\n" << std::endl;
	std::cout << "temp : " << &temp << std::endl;
	std::cout << "stringPTR : " << stringPTR << std::endl;
	std::cout << "stringREF : " << &stringREF << std::endl << std::endl;
	std::cout << "Value\n" << std::endl;
	std::cout << "temp : " << temp << std::endl;
	std::cout << "stringPTR : " << *stringPTR << std::endl;
	std::cout << "stringREF : " << stringREF << std::endl << std::endl;

	return (0);
}