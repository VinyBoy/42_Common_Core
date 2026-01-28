/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:48:58 by viny              #+#    #+#             */
/*   Updated: 2025/12/02 13:33:09 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Span.hpp"
#include <vector>
#include <list>
#include <string>

int	main(void)
{
	std::cout << "\n--- Test longest clean ---" << std::endl; 
	try
	{
		Span spanito(9);
	
		spanito.addNumber(14);
		spanito.addNumber(2334);
		spanito.addNumber(3);
		spanito.addNumber(44);
		spanito.addNumber(33);
		spanito.addNumber(4343);
		spanito.addNumber(76);
		spanito.addNumber(80);
		spanito.addNumber(999);
		int longest = spanito.longestSpan();
		std::cout << "longest is (max - min) = " << longest << std::endl;
	} catch (std::exception &e) {
		std::cout << "Error : " << e.what() << std::endl;
	}

	
	std::cout << "\n--- Test longest fail full---" << std::endl; 
	try
	{
		Span spanito(9);
	
		spanito.addNumber(14);
		spanito.addNumber(2334);
		spanito.addNumber(3);
		spanito.addNumber(44);
		spanito.addNumber(33);
		spanito.addNumber(4343);
		spanito.addNumber(76);
		spanito.addNumber(80);
		spanito.addNumber(999);
		spanito.addNumber(1);
		int longest = spanito.longestSpan();
		std::cout << "longest is (max - min) = " << longest << std::endl;
	} catch (std::exception &e) {
		std::cout << "Error : " << e.what() << std::endl;
	}

	
	std::cout << "\n--- Test longest fail 1 element ---" << std::endl; 
	try
	{
		Span spanito(1);
	
		spanito.addNumber(14);
		int longest = spanito.longestSpan();
		std::cout << "longest is (max - min) = " << longest << std::endl;
	} catch (std::exception &e) {
		std::cout << "Error : " << e.what() << std::endl;
	}


	
	std::cout << "\n--- Test shortest clean ---" << std::endl; 
	try
	{
		Span spanito(9);
	
		spanito.addNumber(14);
		spanito.addNumber(2334);
		spanito.addNumber(3);
		spanito.addNumber(44);
		spanito.addNumber(33);
		spanito.addNumber(4343);
		spanito.addNumber(76);
		spanito.addNumber(80);
		spanito.addNumber(999);
		int shortest = spanito.shortestSpan();
		std::cout << "shortest is  " << shortest << std::endl;
	} catch (std::exception &e) {
		std::cout << "Error : " << e.what() << std::endl;
	}
	std::cout << "\n--- Test shortest fail full---" << std::endl; 
	try
	{
		Span spanito(9);
	
		spanito.addNumber(14);
		spanito.addNumber(2334);
		spanito.addNumber(3);
		spanito.addNumber(44);
		spanito.addNumber(33);
		spanito.addNumber(4343);
		spanito.addNumber(76);
		spanito.addNumber(80);
		spanito.addNumber(999);
		spanito.addNumber(1);
		int shortest = spanito.shortestSpan();
		std::cout << "shortest is (max - min) = " << shortest << std::endl;
	} catch (std::exception &e) {
		std::cout << "Error : " << e.what() << std::endl;
	}
	std::cout << "\n--- Test shortest fail 1 element ---" << std::endl; 
	try
	{
		Span spanito(1);
	
		spanito.addNumber(14);
		int shortest = spanito.shortestSpan();
		std::cout << "shortest is (max - min) = " << shortest << std::endl;
	} catch (std::exception &e) {
		std::cout << "Error : " << e.what() << std::endl;
	}
	return (0);
}

// int main()
// {
// Span sp = Span(5);
// sp.addNumber(6);
// sp.addNumber(3);
// sp.addNumber(17);
// sp.addNumber(9);
// sp.addNumber(11);
// std::cout << sp.shortestSpan() << std::endl;
// std::cout << sp.longestSpan() << std::endl;
// return 0;
// }