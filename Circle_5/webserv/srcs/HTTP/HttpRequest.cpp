/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:49:25 by oztozdem          #+#    #+#             */
/*   Updated: 2025/10/22 13:10:38 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/HTTP/HttpRequest.hpp"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <sstream>

HttpRequest::HttpRequest() : _method(""), _url(""), _body(""), _httpVersion("HTTP/1.1"), _complete(false), _valid(false), _isHTTPS(false), _errorMessage("") {}

HttpRequest::HttpRequest(const std::string &method, const std::string &url) : _method(method), _url(url), _complete(false), _valid(false), _isHTTPS(false), _errorMessage("") {
	setPathAndQuery(url);
}

HttpRequest::~HttpRequest() {}

std::string HttpRequest::getMethod() const {
	return _method;
}

std::string HttpRequest::getUrl() const {
	return _url;
}

std::map<std::string, std::string> HttpRequest::getHeaders() const {
	return _headers;
}

std::string HttpRequest::getBody() const {
	return _body;
}

std::string HttpRequest::toString() const {
	std::ostringstream oss;

	oss << _method << " " << _url << " " << _httpVersion << "\r\n";
	for (std::map<std::string, std::string>::const_iterator it = _headers.begin(); it != _headers.end(); ++it) {
		oss << it->first << ": " << it->second << "\r\n";
	}
	oss << "\r\n" << _body;
	return oss.str();
}

std::string HttpRequest::getHttpVersion() const {
	return _httpVersion;
}

std::string HttpRequest::getPath() const {
	return _path;
}

std::string HttpRequest::getQuery() const {
	return _query;
}

void HttpRequest::setMethod(const std::string &method) {
	_method = method;
}

void HttpRequest::setUrl(const std::string &url) {
	_url = url;
}

void HttpRequest::setPathAndQuery(const std::string &url) {
	size_t queryPos = url.find('?');
	if (queryPos != std::string::npos) {
    	_path = url.substr(0, queryPos);
    	_query = url.substr(queryPos + 1);
  	}
	else {
    	_path = url;
    	_query = "";
  	}
}

void HttpRequest::setHttpVersion(const std::string &version) {
	_httpVersion = version;
}

void HttpRequest::addHeader(const std::string &key, const std::string &value) {
	_headers[key] = value;
}

void HttpRequest::setBody(const std::string &body) {
	_body = body;
}

void HttpRequest::setComplete(bool complete) {
	_complete = complete;
}

void HttpRequest::setValid(bool valid) {
	_valid = valid;
}

bool HttpRequest::isComplete() const {
	return _complete;
}

bool HttpRequest::isValid() const {
	if (_method.empty() || _url.empty() || _httpVersion.empty()) {
		return false;
  	}
	if (_httpVersion != "HTTP/1.1") {
		return false;
	}
	if (_httpVersion == "HTTP/1.1" && _headers.find("Host") == _headers.end()) {
		return false;
	}
	return true;
}

bool HttpRequest::isHTTPS() const {
	return _isHTTPS;
}

std::string HttpRequest::getErrorMessage() const {
	return _errorMessage;
}

HttpRequest HttpRequest::parseHttpRequest(const std::string &raw) {
	HttpRequest req;

	if (raw.length() >= 2 && (unsigned char)raw[0] == 0x16) {
		req._isHTTPS = true;
		req._valid = false;
		req._errorMessage = "HTTPS not supported. Use HTTP instead.";
		return req;
	}
	size_t headerEnd = raw.find("\r\n\r\n");
	if (headerEnd == std::string::npos) {
		req._errorMessage = "Incomplete HTTP request";
		return req;
	}
	size_t checkLength = std::min(headerEnd, (size_t)500);
	for (size_t i = 0; i < checkLength; i++) {
		char c = raw[i];
		if (!isprint(c) && c != '\r' && c != '\n' && c != '\t') {
			req._valid = false;
			req._errorMessage = "Invalid characters in HTTP headers";
			return req;
		}
	}

	std::string::size_type pos = 0;
	std::string::size_type end;

	end = raw.find("\r\n", pos);
	if (end == std::string::npos) {
		req._errorMessage = "Invalid HTTP request format";
		return req;
	}
	std::string startLine = raw.substr(pos, end - pos);
	pos = end + 2;

	std::istringstream iss(startLine);
	std::string method, url, version;
	iss >> method >> url >> version;
	req.setMethod(method);
	req.setUrl(url);
	req.setPathAndQuery(url);
	req.setHttpVersion(version);

	while (true) {
		end = raw.find("\r\n", pos);
		if (end == std::string::npos)
			break;
		std::string line = raw.substr(pos, end - pos);
		pos = end + 2;
		if (line.empty())
			break;

		std::string::size_type colon = line.find(':');
		if (colon != std::string::npos) {
			std::string key = line.substr(0, colon);
			std::string value = line.substr(colon + 1);
			while (!value.empty() && (value[0] == ' ' || value[0] == '\t'))
				value.erase(0, 1);
			req.addHeader(key, value);
		}
	}

	if (pos < raw.size()) {
		req.setBody(raw.substr(pos));
	}

	req.setComplete(true);
	req.setValid(req.isValid());

	return req;
}

std::string HttpRequest::getHeader(const std::string &key) const {
	std::map<std::string, std::string>::const_iterator it = _headers.find(key);
	
	if (it != _headers.end()) {
		return it->second;
	}
	return "";
}

std::string HttpRequest::getPort() const {
	std::string host = getHeader("Host");
	if (!host.empty()) {
		size_t colonPos = host.find(":");
    	if (colonPos != std::string::npos) {
			return host.substr(colonPos + 1);
    	}
  }
  return "8080";
}
