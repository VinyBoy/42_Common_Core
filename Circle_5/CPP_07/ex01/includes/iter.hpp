/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:28:53 by viny              #+#    #+#             */
/*   Updated: 2025/11/23 18:06:25 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

template <typename T, typename F>
void Iter(T *array, size_t len, F function)
{
	for (size_t i = 0; i < len; i++)
		function(array[i]);
}

template <typename T, typename F>
void Iter(const T *array, size_t len, F function)
{
	for (size_t i = 0; i < len; i++)
		function(array[i]);
}
