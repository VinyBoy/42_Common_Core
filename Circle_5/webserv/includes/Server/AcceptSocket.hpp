/* ************************************************************************** */
/*																																						*/
/*																												:::
 * ::::::::	 */
/*	 AcceptSocket.hpp
 * :+:			:+:		:+:	 */
/*																										+:+
 * +:+				 +:+		 */
/*	 By: oztozdem <oztozdem@student.42.fr>
 * +#+	+:+			 +#+				*/
/*																								+#+#+#+#+#+
 * +#+					 */
/*	 Created: 2025/10/15 16:02:39 by oztozdem
 * #+#		#+#						 */
/*	 Updated: 2025/10/15 16:03:38 by oztozdem
 * ###	 ########.fr			 */
/*																																						*/
/* ************************************************************************** */

#pragma once

#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class AcceptSocket {
public:
  AcceptSocket(int listenfd);
  ~AcceptSocket();
  AcceptSocket(const AcceptSocket &cpy);
  AcceptSocket &operator=(const AcceptSocket &assign);

  int getAcceptFd() const;
  int releaseAcceptFd();

private:
  int _accepting_fd;
  bool _owned;
};