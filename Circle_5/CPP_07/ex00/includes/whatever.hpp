Fa/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:28:53 by viny              #+#    #+#             */
/*   Updated: 2025/11/23 18:02:34 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

template <typename T>
void swap (T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

template <typename T>
T const min(const T &a, const T &b)
{
	if (a < b)
		return (a);
	else 
		return (b);
}

template <typename T>
T const max(const T &a, const T &b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

class Whatever {

private :

    Whatever(void);
    ~Whatever(void);
    Whatever(const Whatever &cpy);    
    Whatever& operator=(const Whatever &assign);
};
