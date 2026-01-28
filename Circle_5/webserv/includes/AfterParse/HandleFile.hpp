/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleFile.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:00:51 by caspar            #+#    #+#             */
/*   Updated: 2025/10/15 14:49:01 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <exception>

#define OK 200
#define NOTFOUND 404
#define FORBIDDEN 403

class HandleFile
{
    private:
		std::string		_path;
		int				_code_status;
    public:
        HandleFile();
		HandleFile(const std::string& path);
        ~HandleFile();
     
        void			setFileTag(const std::string& path);
        std::string		getFileTag() const;

		int				getCode() const;

		bool			isFile();
        bool            isDirectory();
        bool            canRead();
        
        std::string     readFile(const std::string& path);

		class FileFailed : public std::exception {
			const char* what() const throw() {
				return ("Error when opening file");
			}
		};
};
