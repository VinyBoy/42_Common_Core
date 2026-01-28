/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scalar.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:37:11 by viny              #+#    #+#             */
/*   Updated: 2025/11/16 15:45:48 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>

/* 
	- Une classe non instenciable
		-Forme canonique privee
	- Une methode statique
*/
class ScalarConverter
{
	public :
		static void convert(const std::string &input);
	private :
		ScalarConverter();
		~ScalarConverter();
		ScalarConverter(const ScalarConverter &cpy);
		ScalarConverter & operator=(const ScalarConverter &assign);	
}; 