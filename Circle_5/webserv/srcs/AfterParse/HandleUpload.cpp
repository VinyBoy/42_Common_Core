/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleUpload.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:02:33 by caspar            #+#    #+#             */
/*   Updated: 2025/10/20 18:58:40 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/AfterParse/HandleUpload.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>

HandleUpload::HandleUpload() {}

HandleUpload::HandleUpload(const std::string& path)
{
    this->_upload_path = path;
}

HandleUpload::~HandleUpload() {}

void    HandleUpload::setUpload(const std::string& path)
{
    _upload_path = path;
}

void    HandleUpload::setInput(const std::string& str)
{
    _input = str;
}

void    HandleUpload::setFile(const std::string& file)
{
    _file = file;
}

std::string	HandleUpload::getUpload() const
{
	return (_upload_path);
}

std::string	HandleUpload::getInput() const
{
	return (_input);
}

std::string	HandleUpload::getFile() const
{
	return (_file);
}

bool	HandleUpload::save()
{
    struct stat st;

	if (_upload_path.empty() || _file.empty() || _input.empty())
        return (false);
    if (stat(const_cast<char *>(_upload_path.c_str()), &st) != 0)
	{
		if (mkdir(_upload_path.c_str(), 0755) == -1)
			return (false);
	}
	else
	{
		if (!S_ISDIR(st.st_mode))
			return (false);
	}
	std::string	full  = _upload_path;
	if (full[full.size() - 1] != '/')
		full += "/";
	full += _file;
	std::ofstream outfile(full.c_str(), std::ios::binary);
	if (!outfile)
		return (false);
	outfile.write(_input.c_str(), _input.size());
	outfile.close();
	return (true);
}
