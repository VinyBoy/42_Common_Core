/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenSocket.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:04:58 by viny              #+#    #+#             */
/*   Updated: 2025/10/08 15:21:40 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fcntl.h>
#include <unistd.h>

class OpenSocket
{
	public :

		OpenSocket(int acceptfd);
		~OpenSocket();
		OpenSocket(const std::string& data);
		OpenSocket(const OpenSocket & cpy);
		OpenSocket & operator=(const OpenSocket & assign);

		int	getOpenFd(void) const;

	private :
		int	_log_fd;	
};