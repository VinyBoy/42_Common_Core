/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:25:14 by oztozdem          #+#    #+#             */
/*   Updated: 2025/10/03 11:25:14 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ConfigParser/ConfigParser.hpp"
#include <fstream>
#include <iostream>
#include <sstream>	

ConfigParser::ConfigParser() : _pos(0), _error(false) {}

ConfigParser::~ConfigParser() {}

void ConfigParser::setError(const std::string &msg) {
	_error = true;
	_errorMsg = msg;
}

bool ConfigParser::hasError() const {
	return _error;
}

std::string ConfigParser::getError() const {
	return _errorMsg;
}

std::string ConfigParser::nextToken() {
	if (_pos < _tokens.size())
		return _tokens[_pos++];
	return "";
}

bool ConfigParser::hasMoreTokens() const {
	return _pos < _tokens.size();
}

void ConfigParser::tokenize(const std::string &file_content) {
	_tokens.clear();
	_pos = 0;
	std::string token;
	for (size_t i = 0; i < file_content.size(); i++) {
		char c = file_content[i];
		if (c == '{' || c == '}' || c == ';') {
			if (!token.empty()) {
				_tokens.push_back(token);
				token = "";
			}
			_tokens.push_back(std::string(1, c));
		}
		else if (isspace(c)) {
			if (!token.empty()) {
				_tokens.push_back(token);
				token = "";
			}
		}
		else
			token += c;
	}
	if (!token.empty())
		_tokens.push_back(token);
}

void ConfigParser::parseLocation(ServerConfig &server) {
	LocationConfig loc;
	loc.path = nextToken();
	if (loc.path.empty()) {
		setError("Missing path for location");
		return;
	}
	if (nextToken() != "{") {
		setError("Expected '{' after location path");
		return;
	}

	while (hasMoreTokens()) {
		std::string key = nextToken();
		if (key == "}")
			break;

		if (key == "allowed_methods") {
			while (hasMoreTokens()) {
				std::string method = nextToken();
				if (method == ";")
					break;
				loc.allowed_methods.push_back(method);
			}
		}
		else if (key == "return") {
			std::string code = nextToken();
			std::string url = nextToken();
			if (code.empty() || url.empty()) {
				setError("Missing code or URL for return directive");
				return;
			}
			if (nextToken() != ";") {
				setError("Expected ';' after return directive");
				return;
			}
			loc.redirect_code = atoi(code.c_str());
			loc.redirect_url = url;
			loc.has_redirect = true;
		}
		else {
			std::string value = nextToken();
			if (value.empty()) {
				setError("Missing value for " + key);
				return;
			}
			if (nextToken() != ";") {
				setError("Expected ';' after " + key);
				return;
			}

			if (key == "root")
				loc.root = value;
			else if (key == "index")
				loc.index = value;
			else if (key == "autoindex")
				loc.autoindex = (value == "on");
			else if (key == "upload")
				loc.upload = value;
			else if (key == "cgi_extension")
				loc.cgi_extension = value;
			else if (key == "cgi_path")
				loc.cgi_path = value;
			else if (key == "client_max_body_size") {
				size_t multiplier = 1;
				std::string sizeStr = value;
				if (!sizeStr.empty()) {
					char lastChar = sizeStr[sizeStr.length() - 1];
					if (lastChar == 'M' || lastChar == 'm') {
						multiplier = 1024 * 1024;
						sizeStr = sizeStr.substr(0, sizeStr.length() - 1);
					}
					else if (lastChar == 'K' || lastChar == 'k') {
						multiplier = 1024;
						sizeStr = sizeStr.substr(0, sizeStr.length() - 1);
					}
				}
				loc.client_max_body_size = atoi(sizeStr.c_str()) * multiplier;
			}

			else {
				setError("Unknown directive in location: " + key);
				return;
			}
		}
	}

	server.locations.push_back(loc);
}

void ConfigParser::parseServer() {
	ServerConfig server;
	if (nextToken() != "{") {
		setError("Expected '{' after server");
		return;
	}

	while (hasMoreTokens()) {
		std::string key = nextToken();
		if (key == "}")
			break;

		if (key == "listen") {
			std::string val = nextToken();
			if (val.empty()) {
				setError("Missing value for listen");
				return;
			}
			server.listen = atoi(val.c_str());
			if (nextToken() != ";") {
				setError("Expected ';' after listen");
				return;
			}
		}
		else if (key == "server_name") {
			std::string val = nextToken();
			if (val.empty()) {
				setError("Missing value for server_name");
				return;
			}
			server.server_name = val;
			if (nextToken() != ";") {
				setError("Expected ';' after server_name");
				return;
			}
		}
		else if (key == "error_page") {
			std::string codeStr = nextToken();
			std::string page = nextToken();
			if (codeStr.empty() || page.empty()) {
				setError("Missing value for error_page");
				return;
			}
			int code = atoi(codeStr.c_str());
			if (nextToken() != ";") {
				setError("Expected ';' after error_page");
				return;
			}
			server.error_pages[code] = page;
		}
		else if (key == "location") {
			parseLocation(server);
			if (_error)
				return;
		}
		else {
			setError("Unknown directive in server block: " + key);
			return;
		}
	}

	_servers.push_back(server);
}

void ConfigParser::parseFile(const std::string &filename) {
	std::ifstream file(filename.c_str());
	if (!file) {
		std::cerr << "Could not open file: " << filename << std::endl;
		return;
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	tokenize(buffer.str());

	while (hasMoreTokens()) {
		std::string token = nextToken();
		if (token == "server")
			parseServer();
	}
}

std::vector<ServerConfig> ConfigParser::getServers() const {
	return _servers;
}

void ConfigParser::validateServers() {
	std::map<std::pair<int, std::string>, bool> usedCombinations;

	for (std::vector<ServerConfig>::const_iterator it = _servers.begin(); it != _servers.end(); ++it) {
		const ServerConfig &server = *it;
		std::pair<int, std::string> key = std::make_pair(server.listen, server.server_name);
		if (usedCombinations[key]) {
			std::ostringstream oss;
			oss << server.listen;
			throw std::runtime_error("Duplicate server: " + server.server_name + ":" + oss.str());
		}
		usedCombinations[key] = true;
	}
}
