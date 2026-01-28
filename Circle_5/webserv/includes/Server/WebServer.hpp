/* ************************************************************************** */
/*																																						*/
/*																												:::
 * ::::::::	 */
/*	 WebServer.hpp
 * :+:			:+:		:+:	 */
/*																										+:+
 * +:+				 +:+		 */
/*	 By: oztozdem <oztozdem@student.42.fr>
 * +#+	+:+			 +#+				*/
/*																								+#+#+#+#+#+
 * +#+					 */
/*	 Created: 2025/09/30 10:41:29 by viny
 * #+#		#+#						 */
/*	 Updated: 2025/10/15 16:06:31 by oztozdem
 * ###	 ########.fr			 */
/*																																						*/
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <map>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include "../AfterParse/Router.hpp"
#include "../ConfigParser/ConfigParser.hpp"

#define PORT 8080

class ListeningSocket;
class AcceptSocket;

class WebServer {
public:
  WebServer(const std::string &configFile);
  ~WebServer();
  WebServer(const WebServer &cpy);
  WebServer &operator=(const WebServer &assign);

  void init();
  void run();
  void stop();

private:
  std::string _configFile;
  ConfigParser _parser;
  std::vector<ServerConfig> _configs;

  std::vector<ListeningSocket *> _listenSockets;
  std::vector<struct pollfd> _pollfds;
  std::map<int, ServerConfig> _fdToConfig;
  std::map<int, size_t> _listenFdToConfigIndex;
  std::map<int, std::string> _clientBuffers;

  bool _running;

  void parseConfig();
  void createListenSockets();
  void setNonBlocking(int fd);
  void handleNewConnection(int listenFd, const ServerConfig &config);
  void handleClientData(int clientFd);
  void closeConnection(int clientFd);
  void cleanupSockets();
  void setupRouter(Router &router, const ServerConfig &config);

  void fatal(const char *msg);
};

#endif