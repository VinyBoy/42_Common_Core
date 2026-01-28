/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenSocket.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:21:14 by viny              #+#    #+#             */
/*   Updated: 2025/10/15 17:55:43 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server/OpenSocket.hpp"

OpenSocket::OpenSocket(int acceptfd) : _log_fd(-1)
{
	char	buf[1024];
	ssize_t n;
	_log_fd = open("socket_log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (_log_fd < 0)
		throw std::runtime_error("open() failed");
	while ((n = read(acceptfd, buf, sizeof(buf))) > 0)
		write(_log_fd, buf, n);
	if (n < 0)
		throw std::runtime_error("read() failed");
	return ;
}

OpenSocket::OpenSocket(const std::string& data) : _log_fd(-1)
{
    _log_fd = open("socket_log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (_log_fd < 0)
        throw std::runtime_error("open() failed");
    
    write(_log_fd, data.c_str(), data.length());
    write(_log_fd, "\n--- End of Request ---\n", 24);
}

OpenSocket::~OpenSocket(void)
{
	close (_log_fd);
}

OpenSocket::OpenSocket(const OpenSocket &cpy)
{
	*this = cpy;
}

OpenSocket & OpenSocket::operator=(const OpenSocket &assign)
{
	if (this != &assign)
	{
		this->_log_fd = assign.getOpenFd();
	}
	return (*this);
}

int	OpenSocket::getOpenFd(void) const
{
	return (_log_fd);
}