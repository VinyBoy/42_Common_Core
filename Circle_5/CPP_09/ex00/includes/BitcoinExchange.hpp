/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:37:50 by viny              #+#    #+#             */
/*   Updated: 2025/12/05 15:34:11 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <exception>

class BitcoinExchange
{
	public :
		BitcoinExchange(const std::string &path);
		BitcoinExchange(const BitcoinExchange &cpy);
		BitcoinExchange & operator=(const BitcoinExchange &assign);
		~BitcoinExchange();

		void	printData();
		void	parseFile(char *input);
		void	parseLine(const std::string &line);
		bool	parseFirstLine(const std::string &firstLine);
		bool	isValidDate(const std::string &date);
	private :
		std::string _path;
		std::map<std::string , float> _data;
		
	
};