/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:40:07 by viny              #+#    #+#             */
/*   Updated: 2025/12/14 11:14:58 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string &path) : _path(path), _data()
{
	std::ifstream file(_path.c_str());
	if (!file.is_open())
	throw std::runtime_error("Can't open the file " + path);
	
	std::map<std::string, float> init;
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string date;
		std::string valueStr;
		
		if (std::getline(ss, date, ',') && std::getline(ss, valueStr))
		{
			float value;
			std::stringstream(valueStr) >> value;
			_data[date] = value;
		}
	}
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &cpy) : _path(cpy._path), _data() {}

BitcoinExchange & BitcoinExchange::operator=(const BitcoinExchange &assign)
{
	if (this != &assign)
	{
		_data = assign._data;
		_path = assign._path;
	}
	return (*this);
}

void	BitcoinExchange::printData()
{
	std::map<std::string, float>::iterator it;
	for (it = _data.begin(); it != _data.end(); it++)
	{
		std::cout << it->first << " : " << it->second << "\n";
	}
}

void	BitcoinExchange::parseFile(char *input)
{
	if (!input)
		throw (std::runtime_error("Input is NULL"));
		
	std::ifstream file(input);
	if (!file.is_open())
		throw (std::runtime_error("could not open file."));

	std::string line;
	bool firstLine = true;
	
	while (std::getline(file, line))
	{
		if (firstLine)
		{
			if (parseFirstLine(line))
				firstLine = false;
			else
				throw (std::runtime_error("Bad first Line"));
			continue ;
		}
		parseLine(line);
	}
}

void	BitcoinExchange::parseLine(const std::string &line)
{

	size_t pipePosition = line.find('|');
	if (pipePosition == std::string::npos)
	{
		std::cerr << "Error : Bad input => " << line << std::endl;
		return ;
	}

	std::string date = line.substr(0, pipePosition - 1);
	std::string value = line.substr(pipePosition + 1);
		
	float finalValue;
	std::stringstream ss(value);
    if (!(ss >> finalValue) || !ss.eof())
    {
        std::cerr << "Error: bad input => " << line << std::endl;
        return;
    }
    
    if (finalValue < 0)
    {
        std::cerr << "Error: not a positive number." << std::endl;
        return;
    }
    
    if (finalValue > 1000)
    {
        std::cerr << "Error: too large a number." << std::endl;
        return;
    }

	if (isValidDate(date))
		std::cout << date << " => ";
	else
	{
		std::cerr << "Error : Bad input => " << line << std::endl;
		return ;
	}
	std::map<std::string, float>::iterator it = _data.lower_bound(date);
	float rate = it->second;
	float result = rate * finalValue;
	std::cout << finalValue << " = " << result << std::endl;
	
}

bool	BitcoinExchange::parseFirstLine(const std::string &firstLine)
{
	std::stringstream ss(firstLine);
	std::string word1, word2, word3;

	ss >> word1 >> word2 >> word3;
	if (word1 == "date" && word2 == "|" && word3 == "value")
		return (true);
	return (false);
}

bool	BitcoinExchange::isValidDate(const std::string &date)
{
	if (date.length() != 10)
		return (false);

	std::string YYYY = date.substr(0, 4);
	std::string MM = date.substr(5, 2);
	std::string DD = date.substr(8, 2);
	
    if (YYYY.find_first_not_of("0123456789") != std::string::npos)
        return false;
    if (MM.find_first_not_of("0123456789") != std::string::npos)
        return false;
    if (DD.find_first_not_of("0123456789") != std::string::npos)
    {
		return false;
	}

	int year, month, day;
    std::stringstream(YYYY) >> year;
    std::stringstream(MM) >> month;
    std::stringstream(DD) >> day;
	
	if (year < 2009 || year > 2025)
		return (false);
	if (month < 1 || month > 12)
		return (false);
	if (day < 1)
		return (false);
	
	bool isBisextile = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

	int maxDays;

	switch (month)
	{
	case 1:
		maxDays = 31;
		break;
	case 2:
		if (isBisextile)
			maxDays = 29;
		else
			maxDays = 28;
		break;
	case 3:
		maxDays = 31;
		break;
	case 4:
		maxDays = 30;
		break;
	case 5:
		maxDays = 31;
		break;
	case 6:
		maxDays = 30;
		break;
	case 7:
		maxDays = 31;
		break;
	case 8:
		maxDays = 30;
		break;
	case 9:
		maxDays = 31;
		break;
	case 10:
		maxDays = 30;
		break;
	case 11:
		maxDays = 30;
		break;
	case 12:
		maxDays = 31;
		break;
	default:
		break;
	}

	if (day > maxDays)
		return (false);

	return (true);
}