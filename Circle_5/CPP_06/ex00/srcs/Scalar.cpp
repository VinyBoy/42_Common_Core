/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scalar.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:51:32 by viny              #+#    #+#             */
/*   Updated: 2025/11/18 15:09:33 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Scalar.hpp"
#include <iostream>
#include <iomanip>
#include <cerrno>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <limits>
#include <cctype>


ScalarConverter::ScalarConverter() {}

ScalarConverter::~ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &cpy)
{
	(void)cpy;
}

ScalarConverter & ScalarConverter::operator=(const ScalarConverter &assign)
{
	(void)assign;
	return (*this);
}

void ScalarConverter::convert(const std::string &input)
{
	std::cout << std::fixed << std::setprecision(1);
	
	if (input.empty())
	{
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;		
	}
	else if (input == "nan" || input == "nanf")
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
		return ;
	}
	else if (input == "-inf" || input == "-inff")
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: -inff" << std::endl;
		std::cout << "double: -inf" << std::endl;
		return ;
	}
	else if (input == "+inf" || input == "+inff")
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: +inff" << std::endl;
		std::cout << "double: +inf" << std::endl;
		return ;
	}

	if (input.size() == 3 && input[0] == '\'' && input[2] == '\'')
	{
		char c = input[1];
		unsigned char uc = static_cast<unsigned char>(c);
		if (std::isprint(uc))
			std::cout << "char: '" << c << "'" << std::endl;
		else
			std::cout << "char: Non displayable" << std::endl;
		std::cout << "int: " << static_cast<int>(c) << std::endl;
		std::cout << "float: " << static_cast<float>(c) << "f" << std::endl;
		std::cout << "double: " << static_cast<double>(c) << std::endl;
		return;
	}

	if (input.size() == 1 && std::isprint(static_cast<unsigned char>(input[0])) && !std::isdigit(static_cast<unsigned char>(input[0])))
	{
		char c = input[0];
		unsigned char uc = static_cast<unsigned char>(c);
		if (std::isprint(uc))
			std::cout << "char: '" << c << "'" << std::endl;
		else
			std::cout << "char: Non displayable" << std::endl;
		std::cout << "int: " << static_cast<int>(c) << std::endl;
		std::cout << "float: " << static_cast<float>(c) << "f" << std::endl;
		std::cout << "double: " << static_cast<double>(c) << std::endl;
		return;
	}
	
	errno = 0;
	char *endptr = NULL;
	const char *cstr = input.c_str();
	double d = std::strtod(cstr, &endptr);
	
	if (endptr == cstr)
	{
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;	
	}

    if (!(*endptr == '\0' || (*endptr == 'f' && *(endptr + 1) == '\0')))
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }

    if (errno == ERANGE && !std::isinf(d))
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }

	if (std::isnan(d) || std::isinf(d) || d < 0.0 || d > 127.0)
		std::cout << "char: impossible" << std::endl;
	else
	{
		char ch = static_cast<unsigned char>(d);
		if (std::isprint(static_cast<unsigned char>(ch)))
			std::cout << "char: \'" << ch << "'" << std::endl;
		else
			std::cout << "char: Non displayable" << std::endl;
	}
	
	if (std::isnan(d) || std::isinf(d) ||
		d < static_cast<double>(std::numeric_limits<int>::min()) ||
		d > static_cast<double>(std::numeric_limits<int>::max()))
	{
		std::cout << "int: impossible" << std::endl;
	}
	else
		std::cout << "int: "<< static_cast<int>(d) << std::endl;
	
	if (std::isnan(d))
		std::cout << "float: nanf" << std::endl;
	else if (std::isinf(d))
	{
		if (d > 0)
			std::cout << "float: +inff" << std::endl;
		else
			std::cout << "float: -inff" << std::endl;
	}
	else if (d < -static_cast<double>(std::numeric_limits<float>::max()) ||
			d > static_cast<double>(std::numeric_limits<float>::max()))
	{
		std::cout << "float: impossible" << std::endl;
	}
	else
	{
		float f = static_cast<float>(d);
		std::cout << "float: " << f << "f" << std::endl;
	}

	if (std::isnan(d))
		std::cout << "double: nan" << std::endl;
	else if (std::isinf(d))
	{
		if (d > 0)
			std::cout << "double: +inf" << std::endl;
		else
			std::cout << "double: -inf" << std::endl;
	}
	else
		std::cout << "double: " << d << std::endl;
}