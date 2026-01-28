/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 08:39:44 by viny              #+#    #+#             */
/*   Updated: 2025/12/01 19:50:15 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <algorithm>
#include <exception>
#include <vector>

class Span
{
	public :
		Span(unsigned int n);
		Span(const Span & cpy);
		Span & operator=(const Span & assign);
		~Span();

		void addNumber(int nb);
		int	shortestSpan() const;
		int	longestSpan() const;
		void printData() const;
		
		
		class IsFull : public std::exception
		{
			const char *what() const throw(){
				return ("Is full");
			}
		};
	
	private :
		unsigned int _maxSize;
		std::vector<int>_data;
	
};