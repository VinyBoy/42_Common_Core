/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:16:57 by viny              #+#    #+#             */
/*   Updated: 2025/12/02 13:21:03 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Span.hpp"

Span::Span(unsigned int n) : _maxSize(n) {}

Span::Span(const Span &cpy) : _maxSize(cpy._maxSize) {}

Span & Span::operator=(const Span &assign)
{
	if (this != &assign)
	{
		_maxSize = assign._maxSize;
	}
	return (*this);
}

Span::~Span() {}

void	Span::addNumber(int nb)
{
	if (_data.size() >= _maxSize)
		throw(IsFull());
	_data.push_back(nb);
}

int	Span::shortestSpan() const
{
	if (_data.size() < 2)
		throw (std::runtime_error("Data need more than 1 element"));
	int val1 = 0;
	int val2 = 0;
	int diff = 0;
	std::vector<int> temp = _data;
	std::sort(temp.begin(), temp.end());
	int i = 0;
	int tempo = temp[1] - temp[0];
	for (std::vector<int>::const_iterator it = temp.begin(); it + 1 != temp.end(); it++)
	{
		val1 = temp[i];
		val2 = temp[i + 1];
		diff = val2 - val1;
		if (diff < tempo)
			tempo = diff;
		i++;
	}
	return (tempo);
}

int	Span::longestSpan() const
{
	if (_data.size() < 2)
		throw (std::runtime_error("Data need more than 1 element"));
	int min = *std::min_element(_data.begin(), _data.end());
	int max = *std::max_element(_data.begin(), _data.end());
	int	shortest = max - min;
	return (shortest);
}

void Span::printData() const
{
	for (std::vector<int>::const_iterator it = _data.begin(); it != _data.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}