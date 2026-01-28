/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmerge.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:36:46 by viny              #+#    #+#             */
/*   Updated: 2025/12/21 18:40:55 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

/*
	Forme Canonique
*/
template<typename Container>
PmergeMe<Container>::PmergeMe(const std::string &arguments) : _arg(arguments), _data()
{
	if (!parseArg())
		throw (std::runtime_error("Error"));
}

template<typename Container>
PmergeMe<Container>::PmergeMe(const PmergeMe &cpy) : _data(cpy._data) {}

template<typename Container>
PmergeMe<Container> & PmergeMe<Container>::operator=(const PmergeMe &assign)
{
	if (this != &assign)
	{
		_data = assign._data;
	}
	return (*this);
}

template<typename Container>
PmergeMe<Container>::~PmergeMe() {}


/*
	Parsing
*/
template<typename Container>
bool	PmergeMe<Container>::parseArg()
{
	std::istringstream iss(_arg);
	std::string element;
	
	while (iss >> element)
	{
		size_t i = 0;
		if (element[i] == '+')
			i++;
		
		if (i >= element.length())
			return (false);

		for (; i <element.length(); i++)
		{
			if (!isdigit(element[i]))
				return (false);
		}

		long nb = atol(element.c_str());
		if (nb < 1 || nb > INT_MAX)
				return (false);
		_data.push_back(static_cast<int>(nb));
	}
	if (!checkDouble())
		return (false);
	return (true);
}


template<typename Container>
bool	PmergeMe<Container>::checkDouble()
{
	Container cpy = _data;
	int	i = 0;
	std::sort(cpy.begin(), cpy.end());
	typename Container::iterator it;
	for (it = cpy.begin(); it + 1!= cpy.end(); it++)
	{
		if (*it == *(it + 1))
			throw (std::runtime_error("Error double detected"));
		i++;
	}
	return (true);
}

/*
	Algo
*/


template<typename Container>
void	PmergeMe<Container>::run()
{
	if (typeid(Container) == typeid(std::vector<int>))
	{
		std::cout << "Before: ";
		printContainer(_data);
		Container result;
		result = fordJohnsonVec(_data);
		_data = result;
		std::cout << "After : ";
		printContainer(_data);
	}
	if (typeid(Container) == typeid(std::deque<int>))
	{
		Container result;
		result = fordJohnsonVec(_data);
		_data = result;
	}
}

template<typename Container>
Container PmergeMe<Container>::sortMax(const std::vector<Pair> &pairs)
{
	Container max;
	std::vector<Pair>::const_iterator it;
	for (it = pairs.begin(); it != pairs.end(); it++)
	{
		max.push_back(it->max);
	}
	return (max);
}

template<typename Container>
Container PmergeMe<Container>::fordJohnsonVec(const Container &input)
{
	if (input.size() == 0)
		return (Container());
	else if (input.size() == 1)
		return (input);
	else if (input.size() == 2)
    {
        Container result;
        typename Container::const_iterator it = input.begin();
        int a = *it;
        ++it;
        int b = *it;
        
        if (a > b)
        {
            result.push_back(b);
            result.push_back(a);
        }
        else
        {
            result.push_back(a);
            result.push_back(b);
        }
        return (result);
    }

	std::vector<Pair> pairs;
	int orphan = formPair(pairs, input);
	
    Container max = sortMax(pairs);

    Container sortedMax = fordJohnsonVec(max);
    
    std::vector<Pair> sortedPairs;
    for (typename Container::const_iterator maxIt = sortedMax.begin(); maxIt != sortedMax.end(); ++maxIt)
    {
        for (size_t i = 0; i < pairs.size(); i++)
        {
            if (pairs[i].max == *maxIt)
            {
                sortedPairs.push_back(pairs[i]);
                break;
            }
        }
    }

    Container mainChain = sortedMax;

    if (!sortedPairs.empty())
	{
    	mainChain.insert(mainChain.begin(), sortedPairs[0].min);
	}

	if (sortedPairs.size() > 1)
	{
		size_t limit = sortedPairs.size() - 1; 
		std::vector<size_t> order = jacobsthalInsertionOrder(limit);

		for (size_t t = 0; t < order.size(); ++t)
		{
			size_t i = order[t];

			typename Container::iterator itMax = std::find(mainChain.begin(), mainChain.end(), sortedPairs[i].max);
			
			typename Container::iterator pos = std::lower_bound(mainChain.begin(), itMax, sortedPairs[i].min);
			
			mainChain.insert(pos, sortedPairs[i].min);
		}
	}

	if (orphan != -1)
	{
		typename Container::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), orphan);
		mainChain.insert(pos, orphan);
	}
	return (mainChain);	
}

template<typename Container>
int	PmergeMe<Container>::formPair(std::vector<Pair> &pairs, const Container &input)
{
	int	orphan = -1;	
	typename Container::const_iterator it = input.begin();
	size_t i = 0;
	size_t size = input.size();
	while (i + 1 < size)
	{
		Pair p;
		int p1 = *it;
		++it;
		int p2 = *it;
		++it;
		if (p1 < p2)
		{
			p.min = p1;
			p.max = p2;
		}
		else
		{
			p.min = p2;
			p.max = p1;
		}
		pairs.push_back(p);
		i += 2;
	}
	if (size % 2 != 0)
		orphan = *it;
	return (orphan);
}

template<typename Container>
std::vector<size_t> PmergeMe<Container>::jacobsthalInsertionOrder(size_t limit)
{
	std::vector<size_t> order;
	if (limit == 0)
		return (order);
	order.push_back(1);
	size_t prev = 1;

	std::vector<size_t> bounds = jacobsthalBounds(limit);
	
	for (size_t k = 0; k < bounds.size(); ++k)
	{
		size_t cur = bounds[k];
		if (cur <= prev)
			continue;
		
		for (size_t j = cur; j > prev; --j)
			order.push_back(j);
		
		prev = cur;
		if (prev == limit)
			return (order);
	}
	
	for (size_t j = limit; j > prev; --j)
		order.push_back(j);

	return (order);
}

template<typename Container>
std::vector<size_t> PmergeMe<Container>::jacobsthalBounds(size_t limit)
{
	std::vector<size_t> bounds;
	if (limit == 0)
		return (bounds);
	
	/*
		Jacobsthal J0 = 0 // J1 = 1 //  Jn = J(n - 1) + 2*j(n - 2)
	*/
	size_t j0 = 0;
	size_t j1 = 1;

	while(true)
	{
		size_t j2 = j1 + 2 * j0;
		if (j2 > limit)
			break;
		bounds.push_back(j2);
		j0 = j1;
		j1 = j2;
	}
	return (bounds);
}

/*
	Helpers
*/

template<typename Container>
void	PmergeMe<Container>::printContainer(const Container &input)
{
	typename Container::const_iterator it;

	for (it = input.begin(); it != input.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

template<typename Container>
void	PmergeMe<Container>::printPair(const std::vector<Pair>&pair)
{
	std::vector<Pair>::const_iterator it;
	for (it = pair.begin(); it != pair.end(); it++)
	{
		std::cout << "(" << it->min << "," << it->max << ") ";
	}
}

template<typename Container>
size_t PmergeMe<Container>::getNbOfArg() const
{
    return (_data.size());
}
// Instantiations explicites à la fin
template class PmergeMe<std::vector<int> >;
template class PmergeMe<std::deque<int> >;