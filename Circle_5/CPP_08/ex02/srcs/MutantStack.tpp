/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:07:57 by viny              #+#    #+#             */
/*   Updated: 2025/12/02 16:11:04 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MutantStack.hpp"

template<typename T>
MutantStack<T>::MutantStack() : std::stack<T>() {}

template<typename T>
MutantStack<T>::MutantStack(const MutantStack &cpy) : std::stack<T>(cpy) {}

template<typename T>
MutantStack<T> & MutantStack<T>::operator=(const MutantStack &assign) 
{
	if (this != &assign)
		std::stack<T>::operator=(assign);
	return (*this);
}

template<typename T>
MutantStack<T>::~MutantStack() {}