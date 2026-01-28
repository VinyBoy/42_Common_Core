/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:24:00 by oztozdem          #+#    #+#             */
/*   Updated: 2025/10/15 16:07:16 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/HTTP/HttpResponse.hpp"
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <sys/stat.h>

HttpResponse::HttpResponse() : _statusCode(200), _statusMessage("OK") {}

HttpResponse::~HttpResponse() {}

std::string HttpResponse::intToString(int n) {
	std::ostringstream oss;
	oss << n;
	return oss.str();
}


void HttpResponse::setStatus(int code, const std::string& message) {
	_statusCode = code;
	_statusMessage = message;
}

void HttpResponse::setHeader(const std::string& key, const std::string& value) {
	_headers[key] = value;
}

void HttpResponse::setBody(const std::string& body) {
	_body = body;
	_headers["Content-Length"] = intToString(_body.size());
	if (_headers.find("Content-Type") == _headers.end())
		_headers["Content-Type"] = "text/plain";
}

std::string HttpResponse::toString() const {
	std::ostringstream oss;

	oss << "HTTP/1.1 " << _statusCode << " " << _statusMessage << "\r\n";

	for (std::map<std::string, std::string>::const_iterator it = _headers.begin(); it != _headers.end(); ++it) {
                oss << it->first << ": " << it->second << "\r\n";
	}
	oss << "\r\n";
	oss << _body;
	
	return oss.str();
}

bool HttpResponse::fileExists(const std::string& path) {
	struct stat buffer;
	return (stat(path.c_str(), &buffer) == 0);
}

std::string HttpResponse::readFile(const std::string& path) {
	std::ifstream file(path.c_str());
	if (!file.is_open())
		return "";
	std::ostringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

int HttpResponse::getStatusCode() const {
    return _statusCode;
}

std::string HttpResponse::getBody() const {
    return _body;
}

std::map<std::string, std::string> HttpResponse::getHeaders() const {
    return _headers;
}