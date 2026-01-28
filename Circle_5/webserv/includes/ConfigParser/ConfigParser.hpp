/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:24:11 by oztozdem          #+#    #+#             */
/*   Updated: 2025/10/03 11:24:11 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdlib>
#include <map>
#include <string>
#include <vector>

struct LocationConfig {
		std::string path;
		std::string root;
		std::string index;
		bool autoindex;
		std::vector<std::string> allowed_methods;
		std::string upload;
		std::string cgi_extension;
		std::string cgi_path;
		size_t client_max_body_size;
		int redirect_code;
		std::string redirect_url;
		bool has_redirect;

		LocationConfig(): autoindex(false), client_max_body_size(1048576), redirect_code(0), has_redirect(false) {}
};

struct ServerConfig {
		int listen;
		std::string server_name;
		std::map<int, std::string> error_pages;
		std::vector<LocationConfig> locations;
		size_t client_max_body_size;

		ServerConfig() : listen(8080), client_max_body_size(1048576) {}
};

class ConfigParser {
	private:
		std::vector<ServerConfig> _servers;
		std::vector<std::string> _tokens;
		size_t _pos;

		bool _error;
		std::string _errorMsg;
		void setError(const std::string &msg);

		void tokenize(const std::string &file_content);
		void parseServer();
		void parseLocation(ServerConfig &server);

		std::string nextToken();
		bool hasMoreTokens() const;

	public:
		ConfigParser();
		~ConfigParser();

		void parseFile(const std::string &filename);
		std::vector<ServerConfig> getServers() const;
		
		bool hasError() const;
		std::string getError() const;
		void validateServers();
};
