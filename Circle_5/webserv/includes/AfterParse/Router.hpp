/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:18:50 by caspar            #+#    #+#             */
/*   Updated: 2025/10/15 14:57:12 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <exception>
#include <string>
#include "ExecRules.hpp"
#include "../HTTP/HttpResponse.hpp"
#include "../HTTP/HttpRequest.hpp"
#include "../ConfigParser/ConfigParser.hpp"

class HandleCgi;
class HandleUpload; 
class HandleFile;

//Brain

class Router: public ExecRules
{
    private:
		std::vector<ExecRules>		_listRules;

		HttpResponse makeErrorResponse(int code, const std::string& message, const ServerConfig& config) const;
    public:
        Router();
        ~Router();

		void						addRules(const ExecRules& rules);
		HttpResponse				handleRequest(const HttpRequest& request, const ServerConfig& config) const;
		ExecRules					isTheRules(const HttpRequest& request) const;
		
		class NoRules : public std::exception {
			const char* what() const throw() {
				return ("No rules were found");
			}
		};
};

std::string							getTypeFile(const std::string& path);
std::string							sanitizePath(const std::string& path);