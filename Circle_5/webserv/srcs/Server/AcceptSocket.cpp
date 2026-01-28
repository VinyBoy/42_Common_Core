/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AcceptSocket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:10:48 by viny              #+#    #+#             */
/*   Updated: 2025/09/30 16:18:38 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server/AcceptSocket.hpp"
#include <stdexcept>

AcceptSocket::AcceptSocket(int listenfd) : _accepting_fd(-1), _owned(true)
{
	_accepting_fd = accept(listenfd, NULL, NULL);
	if (_accepting_fd < 0)
		throw std::runtime_error("accept() failed");
	return ;
}

AcceptSocket::~AcceptSocket(void)
{
	if (_owned && _accepting_fd >= 0)
        close(_accepting_fd);
}

int AcceptSocket::releaseAcceptFd()
{
    _owned = false;
    return _accepting_fd;
}

AcceptSocket::AcceptSocket(const AcceptSocket &cpy)
{
	*this = cpy;
}

AcceptSocket & AcceptSocket::operator=(const AcceptSocket &assign)
{
	if (this != &assign)
		this->_accepting_fd = assign.getAcceptFd();
	return (*this);
}

int	AcceptSocket::getAcceptFd(void) const
{
	return (_accepting_fd);
}