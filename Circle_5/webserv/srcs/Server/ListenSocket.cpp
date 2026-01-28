/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:11:26 by viny              #+#    #+#             */
/*   Updated: 2025/10/22 14:58:54 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server/ListenSocket.hpp"
#include <iostream>

ListeningSocket::ListeningSocket(int port) : _listening_fd(-1)
{
	_listening_fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (_listening_fd < 0)
		throw std::runtime_error("socket() failed");
	
	int	opt = 1;
	if (setsockopt(_listening_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		throw std::runtime_error("setsockopt() failed");
	
	std::memset(&_addr, 0, sizeof(_addr));
	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	_addr.sin_port = htons(port);

	if (bind(_listening_fd, reinterpret_cast<sockaddr*>(&_addr), sizeof(_addr)) < 0)
		throw std::runtime_error("bind() failed");
	
	if (listen(_listening_fd, 128) < 0)
		throw std::runtime_error("listen() fail ed");
	return ;
}

ListeningSocket::~ListeningSocket(void)
{
	if (_listening_fd >= 0)
	{
		::close(_listening_fd);
		std::cout << "Cleaning socket : " << _listening_fd << " closed" << std::endl;
	}
	return ;
}

ListeningSocket::ListeningSocket(const ListeningSocket &cpy) : _listening_fd(-1)
{
	std::memset(&_addr, 0, sizeof(_addr)); 
	*this = cpy;
}

ListeningSocket & ListeningSocket::operator=(const ListeningSocket &assign)
{
	if (this != &assign)
	{
		if (_listening_fd >= 0)
			close(_listening_fd);
		_addr = assign._addr;
		if (assign._listening_fd >= 0)
		{
			_listening_fd = dup(assign._listening_fd);
			if (_listening_fd < 0)
				throw std::runtime_error("dup() failed");
		}
		else
			_listening_fd = -1;
	}
	return (*this);
}

int		ListeningSocket::getPort(void) const
{
	return (ntohs(_addr.sin_port));
}


int	ListeningSocket::getFd(void) const
{
	return (_listening_fd);
}

sockaddr_in ListeningSocket::getAddr() const
{
	return (_addr);
}