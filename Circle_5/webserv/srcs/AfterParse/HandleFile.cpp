/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleFile.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:02:25 by caspar            #+#    #+#             */
/*   Updated: 2025/10/15 14:48:45 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/AfterParse/HandleFile.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <sstream>

HandleFile::HandleFile() : _code_status(0) {}

HandleFile::HandleFile(const std::string& path)
{
    this->_path = path;
}

HandleFile::~HandleFile() {}

void    HandleFile::setFileTag(const std::string& path)
{
    _path = path;
}

std::string HandleFile::getFileTag() const
{
    return (_path);
}

int HandleFile::getCode() const
{
    return (_code_status);
}

bool    HandleFile::isFile()
{
    struct stat st;

    if (_path.empty())
    {
        _code_status = NOTFOUND;
        return (false);
    }
    if (stat(const_cast<char *>(_path.c_str()), &st) == -1)
    {
		_code_status = NOTFOUND;
        return (false);
    }
    else
    {
        if (S_ISREG(st.st_mode))
		{
			if (access(_path.c_str(), R_OK) == -1)
			{
				_code_status = FORBIDDEN;
				return (false);
			}
			else
			{
				_code_status = OK;
				return (true);
			}
		}
		else
		{
			_code_status = FORBIDDEN;
			return (false);			
		}
    }
}

bool HandleFile::isDirectory()
{
    struct stat st;
    if (stat(_path.c_str(), &st) == -1)
        return false;
    return S_ISDIR(st.st_mode);
}

bool HandleFile::canRead()
{
    return (access(_path.c_str(), R_OK) == 0);
}

std::string HandleFile::readFile(const std::string& path)
{
	std::ifstream   fd(path.c_str(), std::ios::in | std::ios::binary);
	if (!fd)
		throw FileFailed();
	std::ostringstream	buf;
	buf << fd.rdbuf();

	return (buf.str());
}
