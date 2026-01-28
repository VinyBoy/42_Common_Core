/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleCgi.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caspar <caspar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:01:19 by caspar            #+#    #+#             */
/*   Updated: 2025/11/20 15:56:08 by caspar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include <exception>
#include <signal.h>

class HandleCgi
{
    private:
		std::string							_cgi_bin;
		std::string							_script_path;
		std::map<std::string, std::string>	_env;
		std::string							_input;
		std::string							_output;
		unsigned int						_timeout;
		std::map<std::string, std::string>	_response_hd;
		static const size_t					MAX_OUTPUT_SIZE = 10 * 1024 * 1024;
    public:
        HandleCgi();
		HandleCgi(const std::string& cgi_bin, const std::string& script_path);
        ~HandleCgi();

		void								setCGI(const std::string& path);
		void								setScript(const std::string& path);
		void								setEnv(const std::string& key, const std::string& value);
		void								setInput(const std::string& str);
		void								setTimeout(unsigned int seconds);

		std::string							getCGI() const;
		std::string							getScript() const;
		std::map<std::string, std::string>	getEnv() const;
		std::string							getInput() const;
		std::string							getOutput() const;
		std::map<std::string, std::string>	getResponseHd() const;

		void								parseOutput();
		void								cleanFds(int *fd, size_t count);

		void								execute();

		class ForkFailed : public std::exception {
			const char* what() const throw() {
				return ("The fork has failed");
			}
		};

		class PipeFailed : public std::exception {
			const char* what() const throw() {
				return ("The pipe has failed");
			}
		};

		class WriteFailed : public std::exception {
			const char* what() const throw() {
				return ("Write to CGI has failed");
			}
		};

		class ReadingFailed : public std::exception {
			const char* what() const throw() {
				return ("Reading CGI has failed");
			}
		};

		class OutputTooLarge : public std::exception {
			const char* what() const throw() {
				return ("CGI output exceeds maximum size");
			}
		};

		class Timeout : public std::exception {
			const char* what() const throw() {
				return ("CGI execution timeout");
			}
		};
};
