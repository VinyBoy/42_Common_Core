/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 09:58:02 by viny              #+#    #+#             */
/*   Updated: 2025/12/08 14:23:49 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"

Rpn::Rpn(std::string new_rpn) : _rpn(new_rpn), _pile()
{
	if (parseRpn())
	{
		std::cout << _pile.top() << std::endl;
	}
}

Rpn::Rpn(const Rpn &cpy) : _rpn(cpy._rpn), _pile(cpy._pile) {}

Rpn & Rpn::operator=(const Rpn &assign)
{
	if (this != &assign)
	{
		_rpn = assign._rpn;
		_pile = assign._pile;
	}
	return (*this);
}

Rpn::~Rpn() {}

bool Rpn::parseRpn()
{
	std::istringstream iss(_rpn);
	std::string element;

	while (iss >> element)
	{
		if (element.length() == 1 && isdigit(element[0]))
		{
			int newdigit = atoi(element.c_str());
			_pile.push(newdigit);
		}
		else if (isToken(element))
		{
			if (_pile.size() < 2)
				throw (std::runtime_error("Error"));

			int a = _pile.top();
			_pile.pop();
			
			int b = _pile.top();
			_pile.pop();
			
			int newElem;
			if (element[0] == '+')
				newElem = a + b;
			else if (element[0] == '-')
				newElem = b - a;
			else if (element[0] == '*')
				newElem = a * b;
			else if (element[0] == '/')
			{
				if (a == 0)
					throw (std::runtime_error("Error"));
				newElem = b / a;
			}
			_pile.push(newElem);
		}
		else
			throw (std::runtime_error("Error"));
	}
	if (_pile.size() != 1)
		throw (std::runtime_error("Error"));
	return (true);
}

void	Rpn::printStack()
{
	std::stack<int> copie = _pile;
	while (!copie.empty())
	{
		std::cout << copie.top() << std::endl;
		copie.pop();
	}	
}

bool	Rpn::isToken(std::string element)
{
	if (element.length() == 1 && (element[0] == '+'|| element[0] == '-'
		|| element[0] == '*' || element[0] == '/'))
		return (true);
	return (false);
}