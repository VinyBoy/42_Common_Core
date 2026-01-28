/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleCgi.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:02:16 by caspar            #+#    #+#             */
/*   Updated: 2025/10/09 18:45:16 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/AfterParse/HandleCgi.hpp"
#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sstream>
#include <cstdlib>

HandleCgi::HandleCgi() : _timeout(30) {}

HandleCgi::HandleCgi(const std::string& cgi_bin, const std::string& script_path) : _timeout(30)
{
    this->_cgi_bin = cgi_bin;
    this->_script_path = script_path;
}

HandleCgi::~HandleCgi() {}

void    HandleCgi::setCGI(const std::string& path)
{
    _cgi_bin = path;
}

void    HandleCgi::setScript(const std::string& path)
{
    _script_path = path;
}

void    HandleCgi::setEnv(const std::string& key, const std::string& value)
{
    _env[key] = value;
}

void    HandleCgi::setInput(const std::string& str)
{
    _input = str;
}

void	HandleCgi::setTimeout(unsigned int seconds)
{
	_timeout = seconds;
}

std::string	HandleCgi::getCGI() const
{
    return (_cgi_bin);
}

std::string	HandleCgi::getScript() const
{
	return (_script_path);
}

std::map<std::string, std::string>	HandleCgi::getEnv() const
{
	return (_env);
}

std::string	HandleCgi::getInput() const
{
	return (_input);
}

std::string	HandleCgi::getOutput() const
{
	return (_output);
}

std::map<std::string, std::string>	HandleCgi::getResponseHd() const
{
	return (_response_hd);
}

void	HandleCgi::cleanFds(int *fd, size_t count)
{
	for (size_t i = 0; i < count; ++i)
	{
		if (fd[i] != -1)
			close(fd[i]); 
	}
}

void	HandleCgi::parseOutput()
{
	size_t	header_end = _output.find("\r\n\r\n");
	size_t	sep_length = 4;

	if (header_end == std::string::npos)
	{
		header_end = _output.find("\n\n");
		sep_length = 2;
	}
	else
	{
		std::string	hd_str = _output.substr(0, header_end);
		std::string	body = _output.substr(header_end + sep_length);
		std::istringstream	iss(hd_str);
		std::string	line;
		while (std::getline(iss, line))
		{
			if (!line.empty() && line[line.length() - 1] == '\r')
				line.erase(line.length() -1);
			size_t	two_points = line.find(':');
			if (two_points != std::string::npos)
			{
				std::string key = line.substr(0, two_points);
				std::string	value = line.substr(two_points + 1);
				size_t	start = value.find_first_not_of(" \t");
				if (start != std::string::npos)
					value = value.substr(start);
				_response_hd[key] = value;
			}
		}
		_output = body;
	}
}

void	HandleCgi::execute()
{
	std::vector<std::string>	env_str;
	
	for (std::map<std::string, std::string>::const_iterator ite = _env.begin(); ite != _env.end(); ++ite)
		env_str.push_back(ite->first + "=" + ite->second);

	std::vector<char *>			envp;
	for (size_t i = 0; i < env_str.size(); ++i)
		envp.push_back(const_cast<char *>(env_str[i].c_str()));
	envp.push_back(NULL);

	pid_t						child;
	int							input[2];
	int							output[2];
	char						*argv[3];

	if (pipe(input) == -1)
		throw PipeFailed();
	if (pipe(output) == -1)
	{
		cleanFds(input, 2);
		throw PipeFailed();
	}
	child = fork();
	if (child < 0)
	{
		cleanFds(input, 2);
		cleanFds(output, 2);
		throw ForkFailed();
	}
	if (child == 0)
	{
		alarm(_timeout);
		if (dup2(input[0], STDIN_FILENO) == -1)
			exit(1);
		if (dup2(output[1], STDOUT_FILENO) == -1)
			exit(1);
		close(input[0]);
		close(input[1]);
		close(output[0]);
		close(output[1]);

		argv[0] = const_cast<char *>(_cgi_bin.c_str());
		argv[1] = const_cast<char *>(_script_path.c_str());
		argv[2] = NULL;

		if (execve(_cgi_bin.c_str(), argv, &envp[0]) == -1)
			exit(1);
	}
	else
	{
		close (input[0]);
		close (output[1]);
		if (!_input.empty())
		{
			ssize_t written = write(input[1], _input.c_str(), _input.size());
			if (written < 0)
			{
				close (input[1]);
				close (output[0]);
				waitpid(child, NULL, 0);
				throw WriteFailed();
			}
		}
		close(input[1]);

		char					tmp[4096];
		ssize_t					reading;
		_output.clear();
		while ((reading = read(output[0], tmp, sizeof(tmp))) > 0)
		{
			if (_output.size() + reading > MAX_OUTPUT_SIZE)
			{
				close(output[0]);
				kill(child, SIGKILL);
				waitpid(child, NULL, 0);
				throw ReadingFailed();
			}
			_output.append(tmp, reading);
		}
		if (reading < 0)
		{
			close(output[0]);
			kill(child, SIGKILL);
			waitpid(child, NULL, 0);
			throw ReadingFailed();
		}
		close (output[0]);

		int status;
		waitpid(child, &status, 0);
		if (WIFEXITED(status))
        {
			int	exit_code = WEXITSTATUS(status);
			if (exit_code != 0)
			{
				std::ostringstream	oss;
				oss << "CGI exited with status " << exit_code;
				throw std::runtime_error(oss.str());
			}
        }
        else if (WIFSIGNALED(status))
        {
			int	sig = WTERMSIG(status);
			if (sig == SIGALRM)
				throw Timeout();
			std::ostringstream oss;
			oss << "CGI killed by signal " << sig;
            throw std::runtime_error(oss.str());
        }
		parseOutput();
	}
}
