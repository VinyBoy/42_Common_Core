/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:08:07 by viny              #+#    #+#             */
/*   Updated: 2025/12/21 18:37:38 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstring>
#include <exception>
#include <limits.h>
#include <algorithm>
#include <deque>
#include <typeinfo>
#include <ctime>

struct Pair
{
	int	min;
	int	max;
};

template<typename Container>
class PmergeMe
{
	public :
		PmergeMe(const std::string &arg);
		PmergeMe(const PmergeMe &cpy);
		PmergeMe & operator=(const PmergeMe & assign);
		~PmergeMe();

		//Parsing
		bool				parseArg();
		bool				checkDouble();
		
		//Algo
		void				run();
		int					formPair(std::vector<Pair> &pairs, const Container &input);
		Container			fordJohnsonVec(const Container &input);
		Container			sortMax(const std::vector<Pair> &pairs);
		//Jacobsthal
		std::vector<size_t> jacobsthalInsertionOrder(size_t limit);
		std::vector<size_t> jacobsthalBounds(size_t limit);
		
		//Helper
		void				printContainer(const Container &input);
		size_t				getNbOfArg() const;
		void				printPair(const std::vector<Pair>&pair);
		
		private :
		std::string	_arg;
		Container _data;
		clock_t _start_timer;
		clock_t _end_timer;
		
};

#include "../srcs/Pmerge.tpp"