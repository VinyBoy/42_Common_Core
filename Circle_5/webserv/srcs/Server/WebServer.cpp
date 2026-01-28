/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:43:23 by oztozdem          #+#    #+#             */
/*   Updated: 2025/11/24 11:40:46 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server/WebServer.hpp"
#include "../../includes/AfterParse/ExecRules.hpp"
#include "../../includes/AfterParse/Router.hpp"
#include "../../includes/HTTP/HttpRequest.hpp"
#include "../../includes/HTTP/HttpResponse.hpp"
#include "../../includes/Server/AcceptSocket.hpp"
#include "../../includes/Server/ListenSocket.hpp"
#include "../../includes/Server/OpenSocket.hpp"
#include <cstdlib>
#include <errno.h>
#include <exception>
#include <fcntl.h>
#include <iostream>
#include <poll.h>
#include <string>

WebServer::WebServer(const std::string &configFile) : _configFile(configFile) {}

WebServer::~WebServer(void) {
	stop();
}

WebServer::WebServer(const WebServer &cpy) : _configFile(cpy._configFile) {
	*this = cpy;
}

WebServer &WebServer::operator=(const WebServer &assign) {
	if (this != &assign) {
		stop();
		_configFile = assign._configFile;
		_configs = assign._configs;
	}
	return (*this);
}

void WebServer::init() {
	std::cout << "\n🌐 Initialisation WebServer 🌐\n" << std::endl;

	try {
		parseConfig();
		createListenSockets();
		for (size_t i = 0; i < _listenSockets.size(); i++) {
			struct pollfd pfd;
			pfd.fd = _listenSockets[i]->getFd();
			pfd.events = POLLIN;
			pfd.revents = 0;
			_pollfds.push_back(pfd);
			_listenFdToConfigIndex[_listenSockets[i]->getFd()] = i;
		}

		_running = true;

		std::cout << "Webserver initalized with " << _listenSockets.size()
							<< " sockets" << std::endl;
	} catch (const std::exception &e) {
		std::cerr << "Failed to initalize Webserver :" << e.what() << std::endl;
		cleanupSockets();
		_running = false;
		throw;
	}
}

void WebServer::run() {
	if (_listenSockets.empty()) {
		std::cerr << "No listening sockets available" << std::endl;
		return;
	}

	std::cout << "\n" << std::string(50, '=') << std::endl;
	std::cout << "🚀 WEBSERVER RUNNING" << std::endl;
	std::cout << "📡 Listening on ports: ";
	for (size_t i = 0; i < _listenSockets.size(); i++) {
		std::cout << _listenSockets[i]->getPort();
		if (i < _listenSockets.size() - 1)
			std::cout << ", ";
	}
	std::cout << "\n💡 Press Ctrl+C to stop" << std::endl;
	std::cout << std::string(50, '=') << "\n" << std::endl;

	while (_running) {
		int ready = poll(&_pollfds[0], _pollfds.size(), 1000);

		if (ready < 0) {
			if (errno == EINTR)
				continue;
			std::cerr << "poll() error: " << strerror(errno) << std::endl;
			break;
		}

		if (ready == 0)
			continue;

		for (size_t i = 0; i < _pollfds.size() && ready > 0; i++) {
			if (_pollfds[i].revents & POLLIN) {
				if (_listenFdToConfigIndex.find(_pollfds[i].fd) !=
						_listenFdToConfigIndex.end()) {
					size_t configIndex = _listenFdToConfigIndex[_pollfds[i].fd];
					std::cout << "🔗 New connection on port "
										<< _configs[configIndex].listen << std::endl;
					handleNewConnection(_pollfds[i].fd, _configs[configIndex]);
				} else
					handleClientData(_pollfds[i].fd);
				ready--;
			} else if (_pollfds[i].revents & (POLLERR | POLLHUP | POLLNVAL)) {
				std::cout << "❌ Connection error on fd " << _pollfds[i].fd
									<< std::endl;
				closeConnection(_pollfds[i].fd);
				i--;
				ready--;
			}
		}
	}
}

void WebServer::stop(void) {
	_running = false;
	cleanupSockets();
	_pollfds.clear();
	_fdToConfig.clear();
	_listenFdToConfigIndex.clear();
}

void WebServer::parseConfig() {
	if (_configFile.empty()) {
		std::cout << "_config empty" << std::endl;
		return;
	}
	try {
		_parser.parseFile(_configFile);
		if (_parser.hasError())
			throw std::runtime_error("Configuration parsing failed: " +
															 _parser.getError());
		_parser.validateServers();
		_configs = _parser.getServers();
		if (_configs.empty())
			throw std::runtime_error("No server configuration found in file");
		for (size_t i = 0; i < _configs.size(); i++) {
			std::cout << "Server " << i + 1 << ":\n\tPort: " << _configs[i].listen
								<< "\n\tName: " << _configs[i].server_name << std::endl;
		}
	} catch (const std::exception &e) {
		std::cerr << "Error Parsing configuration: " << e.what() << std::endl;
		throw;
	}
}

void WebServer::createListenSockets() {
	if (_configs.empty())
		throw std::runtime_error("No server configurations available");
	size_t succesCount = 0;

	for (size_t i = 0; i < _configs.size(); i++) {
		const ServerConfig &config = _configs[i];

		try {
			ListeningSocket *listenSocket = new ListeningSocket(config.listen);
			if (listenSocket->getFd() < 0) {
				delete listenSocket;
				std::cerr << "Failed to create socket for port " << config.listen
									<< std::endl;
				continue;
			}
			setNonBlocking(listenSocket->getFd());
			_listenSockets.push_back(listenSocket);
			succesCount++;
		} catch (const std::exception &e) {
			std::cerr << "Failed to create socket for port " << config.listen << " : "
								<< e.what() << std::endl;
			/* Pourquoi continue et pas stop?
			continue; */
			stop();
		}
	}
	if (_listenSockets.empty())
		throw std::runtime_error("No listening sockets could be created");
	std::cout << "\nSocket configuration summary\n" << std::endl;
	std::cout << "Total configurations: " << _configs.size() << std::endl;
	std::cout << "Successfully sockets: " << succesCount << std::endl;
	std::cout << "Failed sockets: " << (_configs.size() - succesCount) << "\n"
						<< std::endl;
	std::cout << "Active Listening sockets\n" << std::endl;
	for (size_t i = 0; i < _listenSockets.size(); i++) {
		std::cout << "Sockets " << i << " : Port = " << _listenSockets[i]->getPort()
							<< ", Fd = " << _listenSockets[i]->getFd() << "\n"
							<< std::endl;
	}
}

void WebServer::setNonBlocking(int fd) {
	int flags;

	flags = fcntl(fd, F_GETFL, 0);
	if (flags < 0)
		throw std::runtime_error("fcntl F_GETFL failed");
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0)
		throw std::runtime_error("fcntl F_SETFL failed");
}

void WebServer::handleNewConnection(int listenFd, const ServerConfig &config) {
	try {
		AcceptSocket *acceptSocket = new AcceptSocket(listenFd);
		int clientFd = acceptSocket->releaseAcceptFd();
		if (clientFd < 0) {
			delete acceptSocket;
			return;
		}
		setNonBlocking(clientFd);
		struct pollfd clientPollfd;
		clientPollfd.fd = clientFd;
		clientPollfd.events = POLLIN;
		clientPollfd.revents = 0;
		_pollfds.push_back(clientPollfd);

		_fdToConfig[clientFd] = config;

		std::cout << "✅ Client connected on " << config.server_name << ":"
							<< config.listen << " (fd:" << clientFd << ")" << std::endl;
		delete acceptSocket;
	}
	catch (const std::exception &e) {
		std::cerr << "Error accepting connection " << e.what() << std::endl;
	}
}

void WebServer::handleClientData(int clientFd) {
	try {
		char buffer[8192];
		std::string &requestData = _clientBuffers[clientFd];

		ssize_t bytesRead = recv(clientFd, buffer, sizeof(buffer), 0);
		if (bytesRead <= 0) {
			if (bytesRead == 0)
				std::cout << "👋 Client disconnected (fd:" << clientFd << ")"
									<< std::endl;
			else
				std::cout << "❌ Connection error (fd:" << clientFd << ")" << std::endl;
			closeConnection(clientFd);
			return;
		}

		requestData.append(buffer, bytesRead);

		size_t headerEnd = requestData.find("\r\n\r\n");
		if (headerEnd == std::string::npos) {
			return;
		}

		std::string headers = requestData.substr(0, headerEnd);
		size_t contentLengthPos = headers.find("Content-Length:");
		if (contentLengthPos != std::string::npos) {
			size_t valueStart = contentLengthPos + 15;
			while (valueStart < headers.size() && (headers[valueStart] == ' ' || headers[valueStart] == '\t'))
				valueStart++;
			size_t valueEnd = headers.find('\r', valueStart);
			if (valueEnd != std::string::npos) {
				std::string lengthStr = headers.substr(valueStart, valueEnd - valueStart);
				size_t contentLength = std::atol(lengthStr.c_str());
				size_t bodyStart = headerEnd + 4;
				size_t currentBodySize = requestData.size() - bodyStart;

				if (currentBodySize < contentLength) {
					std::cout << "📊 Received " << currentBodySize << "/" << contentLength
										<< " bytes (fd:" << clientFd << ")" << std::endl;
					return;
				}
			}
		}

		HttpRequest request = HttpRequest::parseHttpRequest(requestData);

		if (request.isHTTPS()) {
			std::cout << "🔒 HTTPS connection rejected: " << request.getErrorMessage()
								<< std::endl;

			const char *httpsResponse =
					"HTTP/1.1 426 Upgrade Required\r\n"
					"Content-Type: text/html\r\n"
					"Content-Length: 120\r\n"
					"Connection: close\r\n"
					"\r\n"
					"<h1>426 Upgrade Required</h1>"
					"<p>This server only supports HTTP. Use: http://localhost:8080</p>";

			send(clientFd, httpsResponse, strlen(httpsResponse), 0);
			closeConnection(clientFd);
			return;
		}

		std::string method = "UNKNOWN";
		std::string path = "/";
		size_t methodEnd = requestData.find(' ');
		if (methodEnd != std::string::npos) {
			method = requestData.substr(0, methodEnd);
			size_t pathEnd = requestData.find(' ', methodEnd + 1);
			if (pathEnd != std::string::npos) {
				path = requestData.substr(methodEnd + 1, pathEnd - methodEnd - 1);
			}
		}

		std::cout << "📥 " << method << " " << path << " from fd:" << clientFd
							<< " (" << bytesRead << " bytes)" << std::endl;
		if (!request.isValid()) {
			std::cout << "❌ Invalid HTTP request from fd:" << clientFd;
			if (!request.getErrorMessage().empty()) {
				std::cout << " - " << request.getErrorMessage();
			}
			std::cout << std::endl;
			const char *errorResponse =
					"HTTP/1.1 400 Bad Request\r\n"
					"Content-Type: text/html\r\n"
					"Content-Length: 47\r\n"
					"Connection: close\r\n"
					"\r\n"
					"<h1>400 Bad Request</h1><p>Invalid request</p>";
			send(clientFd, errorResponse, strlen(errorResponse), 0);
			closeConnection(clientFd);
			return;
		}
		ServerConfig config = _fdToConfig[clientFd];
		OpenSocket *opensocket = new OpenSocket(requestData);
		delete opensocket;
		try {
			Router router;
			setupRouter(router, config);

			HttpResponse response = router.handleRequest(request, config);

			std::string responseStr = response.toString();
			ssize_t sent = send(clientFd, responseStr.c_str(), responseStr.length(), 0);

			if (sent < 0)
				std::cout << "❌ Send error on fd " << clientFd << std::endl;
			else
				std::cout << "📤 Response sent to fd:" << clientFd << " (" << sent
									<< " bytes)" << std::endl;
		}
		catch (const std::exception &routerException) {
			std::cerr << "Router failed: " << routerException.what() << std::endl;

			const char *errorResponse =
					"HTTP/1.1 500 Internal Server Error\r\n"
					"Content-Type: text/html\r\n"
					"Content-Length: 54\r\n"
					"Connection: close\r\n"
					"\r\n"
					"<h1>500 Internal Server Error</h1><p>Server Error</p>";
			send(clientFd, errorResponse, strlen(errorResponse), 0);
		}
		closeConnection(clientFd);
	}
	catch (const std::exception &e) {
		std::cerr << "Error handling client data: " << e.what() << std::endl;
		closeConnection(clientFd);
	}
}

void WebServer::closeConnection(int clientFd) {
	std::cout << "🔌 Closing connection fd:" << clientFd << std::endl;

	close(clientFd);
	_fdToConfig.erase(clientFd);
	_clientBuffers.erase(clientFd);

	for (std::vector<struct pollfd>::iterator it = _pollfds.begin(); it != _pollfds.end(); ++it) {
		if (it->fd == clientFd) {
			_pollfds.erase(it);
			break;
		}
	}
}

void WebServer::cleanupSockets() {
	for (size_t i = 0; i < _pollfds.size(); i++)
		close(_pollfds[i].fd);
	for (size_t i = 0; i < _listenSockets.size(); i++)
		delete _listenSockets[i];
	_listenSockets.clear();
}

void WebServer::fatal(const char *msg) {
	std::cerr << msg << ": " << strerror(errno) << std::endl;
	stop();
	exit(EXIT_FAILURE);
}

void WebServer::setupRouter(Router &router, const ServerConfig &config) {
	for (size_t i = 0; i < config.locations.size(); i++) {
		const LocationConfig &location = config.locations[i];
		ExecRules rules(location.path);
		rules.setRoot(location.root);
		rules.setIndex(location.index);
		if (!location.allowed_methods.empty()) {
			for (size_t j = 0; j < location.allowed_methods.size(); j++) {
				rules.addMethod(location.allowed_methods[j]);
			}
		}
		if (!location.cgi_path.empty()) {
			rules.setCgi(location.cgi_path);
		}
		if (!location.upload.empty()) {
			rules.setUpload(location.upload);
		}
		else if (location.path == "/upload") {
			rules.setUpload("./uploads/");
		}
		if (location.has_redirect) {
			rules.setRedirect(location.redirect_code, location.redirect_url);
		}
		router.addRules(rules);
	}
}
