/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:01:44 by oztozdem          #+#    #+#             */
/*   Updated: 2025/11/24 12:14:46 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/AfterParse/Router.hpp"
#include "../../includes/AfterParse/HandleCgi.hpp"
#include "../../includes/AfterParse/HandleFile.hpp"
#include "../../includes/AfterParse/HandleUpload.hpp"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

std::string intToString(int n) {
	std::stringstream ss;
	ss << n;
	return ss.str();
}

Router::Router() {}

Router::~Router() {}

void Router::addRules(const ExecRules &rules) {
	_listRules.push_back(rules);
}

std::string getTypeFile(const std::string &path) {
	std::map<std::string, std::string> types;
	if (types.empty()) {
		types[".html"] = "text/html";
		types[".htm"] = "text/html";
		types[".txt"] = "text/plain";
		types[".css"] = "text/css";
		types[".js"] = "application/javascript";
		types[".json"] = "application/json";
		types[".png"] = "image/png";
		types[".jpg"] = "image/jpeg";
		types[".jpeg"] = "image/jpeg";
		types[".gif"] = "image/gif";
		types[".svg"] = "image/svg+xml";
		types[".ico"] = "image/x-icon";
		types[".pdf"] = "application/pdf";
	}

	std::string::size_type point = path.find_last_of('.');
	if (point != std::string::npos) {
		std::string extension = path.substr(point);
		std::map<std::string, std::string>::const_iterator ite = types.find(extension);
		if (ite != types.end())
			return (ite->second);
	}
	return ("application/octet-stream");
}

std::string sanitizePath(const std::string &path) {
	std::string sanitized = path;
	size_t pos;

	while ((pos = sanitized.find("../")) != std::string::npos)
		sanitized.erase(pos, 3);
	while ((pos = sanitized.find("..\\")) != std::string::npos)
		sanitized.erase(pos, 3);

	return (sanitized);
}

HttpResponse Router::makeErrorResponse(int code, const std::string &message, const ServerConfig &config) const {
	HttpResponse response;

	std::map<int, std::string>::const_iterator it = config.error_pages.find(code);

	if (it != config.error_pages.end()) {
		std::string errorPagePath = "./www" + it->second;

		try {
			HandleFile errorFile(errorPagePath);
			if (errorFile.isFile() && errorFile.canRead()) {
				std::string content = errorFile.readFile(errorPagePath);
				response.setStatus(code, message);
				response.setBody(content);
				response.setHeader("Content-Type", "text/html");
				return response;
			}
		} catch (std::exception &e) {
			std::cerr << "Error reading custom error page: " << e.what() << std::endl;
		}
	}
	response.setStatus(code, message);
	std::stringstream ss;
	ss << "<h1>" << code << " " << message << "</h1>";
	ss << "<p>Default error page - custom page not found</p>";
	response.setBody(ss.str());
	response.setHeader("Content-Type", "text/html");

	return (response);
}

const LocationConfig* findLocation(const std::string& path, const ServerConfig& config)
{
    const LocationConfig* best = NULL;
    size_t best_len = 0;

    for (size_t i = 0; i < config.locations.size(); ++i) {
        const LocationConfig& loc = config.locations[i];

        if (loc.path.empty())
            continue;

        if (path.compare(0, loc.path.size(), loc.path) == 0) {
            if (loc.path.size() > best_len) {
                best_len = loc.path.size();
                best = &loc;
            }
        }
    }

    return best;
}

static std::string htmlEscape(const std::string &s) {
    std::string out;
    for (size_t i = 0; i < s.size(); i++) {
        switch (s[i]) {
            case '&': out += "&amp;"; break;
            case '<': out += "&lt;"; break;
            case '>': out += "&gt;"; break;
            case '"': out += "&quot;"; break;
            case '\'': out += "&#39;"; break;
            default: out += s[i];
        }
    }
    return out;
}

std::string generateAutoindex(const std::string &fsPath, const std::string &requestPath)
{
    DIR *dir = opendir(fsPath.c_str());
    if (!dir)
        return "<h1>Forbidden</h1>";

    std::stringstream html;

    html << "<html>\n<head><title>Index of " << requestPath << "</title></head>\n";
    html << "<body>\n<h1>Index of " << requestPath << "</h1>\n";
    html << "<ul>\n";

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        std::string name = entry->d_name;

        if (name == "." || name == "..")
            continue;

        std::string fullPath = fsPath + "/" + name;
        struct stat st;
        stat(fullPath.c_str(), &st);

        bool isDir = S_ISDIR(st.st_mode);

        std::string displayName = htmlEscape(name + (isDir ? "/" : ""));
        std::string link = requestPath;
        
        if (link.size() > 1 && link[link.size() - 1] != '/')
            link += "/";

        html << "<li><a href=\"" << link << htmlEscape(name) << (isDir ? "/" : "") 
             << "\">" << displayName << "</a></li>\n";
    }

    closedir(dir);

    html << "</ul></body></html>\n";

    return html.str();
}

HttpResponse Router::handleRequest(const HttpRequest &request, const ServerConfig &config) const {
	HttpResponse response;
	ExecRules rules = isTheRules(request);

	if (rules.hasRedirect()) {
		int code = rules.getRedirectCode();
		std::string message;
		if (code == 301)
			message = "Moved Permanently";
		else if (code == 302)
			message = "Found";
		else if (code == 303)
			message = "See Other";
		else if (code == 307)
			message = "Temporary Redirect";
		else if (code == 308)
			message = "Permanent Redirect";
		else
			message = "Redirect";

		response.setStatus(code, message);
		response.setHeader("Location", rules.getRedirectUrl());
		response.setBody("");
		return response;
	}

	std::string method = request.getMethod();
	std::string requestPath = sanitizePath(request.getPath());
	const LocationConfig* loc = findLocation(requestPath, config);

	size_t max_body_size;
	if (loc && loc->client_max_body_size)
		max_body_size = loc->client_max_body_size;
	else
		max_body_size = config.client_max_body_size;

	if (request.getBody().size() > max_body_size) {
		return makeErrorResponse(413, "Payload Too Large", config);
	}
	
	std::string target;

	std::string rulePath = rules.getPath();
	std::string relativePath = requestPath;

	if (requestPath.find(rulePath) == 0) {
		relativePath = requestPath.substr(rulePath.length());
		if (!relativePath.empty() && relativePath[0] == '/')
			relativePath = relativePath.substr(1);
	}
	if (requestPath == "/" || requestPath.empty())
		target = rules.getRoot() + "/" + rules.getIndex();
	else if (relativePath.empty()) {
		target = rules.getRoot();
		if (!rules.getIndex().empty())
			target += "/" + rules.getIndex();
	}
	else {
		target = rules.getRoot();
		if (target[target.length() - 1] != '/' && relativePath[0] != '/')
			target += "/";
		target += relativePath;
	}
	if (!rules.isMethodAllowed(method))
		return makeErrorResponse(405, "Method Not Allowed", config);

	if (!rules.getCgi().empty()) {
		try {
			struct stat st;
			if (stat(target.c_str(), &st) != 0)
				return makeErrorResponse(404, "Not Found", config);

			if (!(st.st_mode & S_IXUSR) && !(st.st_mode & S_IXGRP) &&
					!(st.st_mode & S_IXOTH))
				return makeErrorResponse(403, "Forbidden", config);

			HandleCgi cgi(rules.getCgi(), target);

			cgi.setInput(request.getBody());
			cgi.setEnv("REQUEST_METHOD", method);
			cgi.setEnv("SERVER_PROTOCOL", request.getHttpVersion());
			cgi.setEnv("GATEWAY_INTERFACE", "CGI/1.1");
			cgi.setEnv("SERVER_SOFTWARE", "Webserv/1.0");
			cgi.setEnv("SCRIPT_FILENAME", target);
			cgi.setEnv("SCRIPT_NAME", request.getPath());
			cgi.setEnv("PATH_INFO", "");
			cgi.setEnv("QUERY_STRING", request.getQuery());

			std::string content_type = request.getHeader("Content-Type");
			if (!content_type.empty())
				cgi.setEnv("CONTENT_TYPE", content_type);

			cgi.setEnv("CONTENT_LENGTH", intToString(request.getBody().size()));
			cgi.setEnv("SERVER_NAME", request.getHeader("Host"));
			cgi.setEnv("SERVER_PORT", request.getPort());

			cgi.execute();

			response.setStatus(200, "OK");
			response.setBody(cgi.getOutput());
			response.setHeader("Content-Type", "text/html");
		}
		catch (std::exception &e) {
			std::cerr << "CGI Error: " << e.what() << std::endl;
			return makeErrorResponse(500, "Internal Server Error", config);
		}
		return (response);
	}

	if (method == "POST" && !rules.getUpload().empty()) {
		try {
			HandleUpload upload(rules.getUpload());

			std::string filename = "upload_file";
			std::string requestPath = request.getPath();

			if (requestPath.find("/upload/") == 0 && requestPath.length() > 8)
				filename = requestPath.substr(8);
			else {
				std::string content_disposition =
						request.getHeader("Content-Disposition");
				if (!content_disposition.empty()) {
					size_t pos = content_disposition.find("filename=");
					if (pos != std::string::npos) {
						pos += 10;
						size_t end = content_disposition.find('"', pos);
						if (end != std::string::npos)
							filename = content_disposition.substr(pos, end - pos);
					}
				}
			}

			if (filename == "upload_file") {
				time_t now = time(0);
				std::stringstream ss;
				ss << "upload_" << now << ".txt";
				filename = ss.str();
			}

			upload.setFile(filename);
			upload.setInput(request.getBody());

			if (upload.save()) {
				response.setStatus(201, "Created");
				response.setBody(
						"<h1>201 Created</h1><p>File has been uploaded successfully</p>");
				response.setHeader("Content-Type", "text/html");
			}
			else
				return makeErrorResponse(501, "Not Implemented", config);
		}
		catch (std::exception &e) {
			return makeErrorResponse(500, "Internal Server Error", config);
		}
		return (response);
	}

	if (method == "POST")
	{
		response.setStatus(200, "OK");
		std::string body = "<h1>200 OK</h1>";
		body += "<p>POST request received successfully</p>";
		body += "<p>Path: " + request.getPath() + "</p>";
		body += "<p>Body length: " + intToString(request.getBody().size()) +
						" bytes</p>";
		response.setBody(body);
		response.setHeader("Content-Type", "text/html");
		return (response);
	}

	if (method == "DELETE") {
		try {
			HandleFile file(target);

			if (file.isFile()) {
				if (remove(target.c_str()) == 0) {
					response.setStatus(204, "No Content");
					response.setHeader("Content-Length", "45");
					response.setBody("<h1>204 No Content</h1><p>File deleted successfully</p>");
				}
				else
					return makeErrorResponse(500, "Internal Server Error", config);
			}
			else if (file.isDirectory()) {
				if (rmdir(target.c_str()) == 0) {
					response.setStatus(204, "No Content");
					response.setHeader("Content-Length", "45");
					response.setBody("<h1>204 No Content</h1><p>Folder deleted successfully</p>");
				}
				else
					return makeErrorResponse(403, "Forbidden", config);
			}
			else
				return makeErrorResponse(404, "Not Found", config);
		}
		catch (std::exception &e) {
			return makeErrorResponse(500, "Internal Server Error", config);
		}
		return (response);
	}

	if (method == "GET") {
		try {
			HandleFile file(target);

			if (file.isFile() && file.canRead()) {
				std::string content = file.readFile(target);
				response.setStatus(200, "OK");
				response.setBody(content);
				response.setHeader("Content-Type", getTypeFile(target));
			}
			else if (file.isDirectory()) {
				std::string reqPath = request.getPath();
				if (reqPath.empty())
					reqPath = "/";

				if (reqPath[reqPath.size() - 1] != '/') {
					response.setStatus(301, "Moved Permanently");
					response.setHeader("Location", reqPath + '/');
					response.setBody("");
				}
				else if (!rules.getIndex().empty()) {
					std::string indexPath = target + "/" + rules.getIndex();
					HandleFile indexFile(indexPath);
					if (indexFile.isFile() && indexFile.canRead()) {
						std::string content = indexFile.readFile(indexPath);
						response.setStatus(200, "OK");
						response.setBody(content);
						response.setHeader("Content-Type", getTypeFile(indexPath));
					}
					else
						return makeErrorResponse(404, "Not Found", config);
				}
				else {
					if (loc && loc->autoindex) {
						std::string html = generateAutoindex(target, request.getPath());

						response.setStatus(200, "OK");
						response.setHeader("Content-Type", "text/html");
						response.setBody(html);
					}
					else {
						return makeErrorResponse(404, "Not Found", config);
    				}
				}
			}
			else
				return makeErrorResponse(404, "Not Found", config);
		}
		catch (std::exception &e) {
			return makeErrorResponse(500, "Internal Server Error", config);
		}
		return (response);
	}

	return makeErrorResponse(501, "Not Implemented", config);
}

ExecRules Router::isTheRules(const HttpRequest &request) const {
	std::string requestPath = request.getPath();

	ExecRules bestMatch;
	size_t bestMatchLength = 0;
	bool found = false;

	for (size_t i = 0; i < _listRules.size(); i++) {
		std::string rulePath = _listRules[i].getPath();

		if (requestPath == rulePath ||
				(requestPath.find(rulePath) == 0 &&
				 (rulePath == "/" || requestPath[rulePath.length()] == '/'))) {
			if (rulePath.length() > bestMatchLength) {
				bestMatch = _listRules[i];
				bestMatchLength = rulePath.length();
				found = true;
			}
		}
	}

	if (found)
		return (bestMatch);

	std::cout << "No matching rule found for: " << requestPath << std::endl;
	if (_listRules.size() > 0)
		return (_listRules[0]);

	return ExecRules("/");
}
