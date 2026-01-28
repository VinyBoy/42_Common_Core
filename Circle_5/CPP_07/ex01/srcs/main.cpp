/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:07:58 by viny              #+#    #+#             */
/*   Updated: 2025/11/23 22:32:48 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "../includes/iter.hpp"

template <typename F> 
void print(const F &p)
{
	std::cout << p << std::endl;
}

template <typename F>
void	addOne(F &n)
{
	n += 10;
}

template <typename F>
void	printString(const F &s)
{
	std::cout << s << std::endl;
}

template <typename F>
void	addOneAscii(F &c)
{
	++c;
}

int main(void)
{
	int tab[] = {1, 2, 3, 4};
	size_t size = 4;
	std::string s1 = "Hello";

	std::cout << "--- Test print int tab ---" << std::endl;
	Iter(tab, size, print<int>);
	std::cout << " --- Test + 10 ---" << std::endl;
	Iter(tab, size, addOne<int>);
	Iter(tab, size, print<int>);
	std::cout << "--- Test print string----" << std::endl;
	Iter(&s1[0], s1.length(), printString<char>);
	std::cout << "--- Test add 1 on ascii table---" << std::endl;
	Iter(&s1[0], s1.length(), addOneAscii<char>);
	Iter(&s1[0],s1.length(), print<char>);
    return (0);
}