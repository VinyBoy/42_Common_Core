/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:41:53 by oztozdem          #+#    #+#             */
/*   Updated: 2025/10/15 17:41:55 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

class	ListeningSocket
{
	public :
	
	ListeningSocket(int port);
	~ListeningSocket(void);
	ListeningSocket(const ListeningSocket & cpy);
	ListeningSocket & operator=(const ListeningSocket & assign);

	int				getFd(void) const;
	int				getPort(void) const;
	sockaddr_in		getAddr(void) const;

	private :
		int 		_listening_fd;
		sockaddr_in	_addr;

};