/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:37:50 by viny              #+#    #+#             */
/*   Updated: 2025/12/21 13:40:19 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>
#include <string>
#include <exception>
#include <sstream>
#include <iostream>
#include <cstring>
#include <stdlib.h>

class Rpn
{
	public :
		Rpn(std::string new_rpn);
		Rpn(const Rpn &cpy);
		Rpn & operator=(const Rpn &assign);
		~Rpn();

		bool	parseRpn();
		void	printStack();
		bool	isToken(std::string element);

	private :
		std::string _rpn;
		std::stack<int> _pile;
	
};