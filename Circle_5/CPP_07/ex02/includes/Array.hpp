/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:28:53 by viny              #+#    #+#             */
/*   Updated: 2025/11/23 23:40:54 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <exception>

template <typename T>
class Array
{
public:
    Array();
    Array(unsigned int n);
    ~Array();
    Array(const Array &cpy);
    Array & operator=(const Array &assign);

    unsigned int getSize() const;
    T & operator[](unsigned int idx);
    const T & operator[](unsigned int idx) const;

    class OutOfRange : public std::exception
    {
    public:
        const char *what() const throw() { return ("Out of range"); }
    };

private:
    T*              _array;
    unsigned int    _size;
};

#include "../srcs/Array.tpp"