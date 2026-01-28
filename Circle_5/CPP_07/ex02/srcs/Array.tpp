/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 22:49:38 by viny              #+#    #+#             */
/*   Updated: 2025/11/23 23:40:07 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Array.hpp"

template <typename T>
Array<T>::Array() : _array(NULL), _size(0) {}

template <typename T>
Array<T>::Array(unsigned int n) : _array(n ? new T[n] : NULL), _size(n) {}

template <typename T>
Array<T>::Array(const Array<T> &cpy) : _array(NULL), _size(0)
{
    if (cpy._size)
    {
        _array = new T[cpy._size];
        _size = cpy._size;
        for (unsigned int i = 0; i < _size; ++i)
            _array[i] = cpy._array[i];
    }
}

template <typename T>
Array<T> & Array<T>::operator=(const Array<T> &assign)
{
    if (this != &assign)
    {
        delete [] _array;
        _array = NULL;
        _size = 0;
        if (assign._size)
        {
            _array = new T[assign._size];
            _size = assign._size;
            for (unsigned int i = 0; i < _size; ++i)
                _array[i] = assign._array[i];
        }
    }
    return (*this);
}

template <typename T>
Array<T>::~Array()
{
    delete [] _array;
}

template <typename T>
unsigned int Array<T>::getSize() const
{
    return (_size);
}

template <typename T>
T & Array<T>::operator[](unsigned int idx)
{
    if (idx >= _size)
        throw OutOfRange();
    return (_array[idx]);
}

template <typename T>
const T & Array<T>::operator[](unsigned int idx) const
{
    if (idx >= _size)
        throw OutOfRange();
    return (_array[idx]);
}