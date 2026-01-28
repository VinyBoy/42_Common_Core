/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caspar <caspar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:51:09 by viny              #+#    #+#             */
/*   Updated: 2025/11/20 18:08:20 by caspar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server/WebServer.hpp"
#include <fcntl.h>
#include <poll.h>
#include <signal.h>
#include <iostream>

WebServer *g_server = NULL;

void	signalHandler(int signal)
{
	std::cout << "\nReceived Signal " << signal << " Stopping Server...\n" << std::endl;
	if (g_server)
		g_server->stop();
	std::cout << "\n🌐 WebServ stopped succesfully ✅" << std::endl;
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage : ./webserv \"server.config\"" << std::endl;
		return (1);
	}
	try
	{
		std::string ConfigFile = argv[1];
		WebServer server(ConfigFile);
		g_server = &server;
		signal(SIGINT, signalHandler);
		signal(SIGQUIT, signalHandler);
		server.init();
		server.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);	
	}

	return (0);
}
