/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleUpload.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:01:48 by caspar            #+#    #+#             */
/*   Updated: 2025/10/09 18:45:16 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class HandleUpload
{
    private:
        std::string		_upload_path;
        std::string		_input;
        std::string		_file;
    public:
        HandleUpload();
        HandleUpload(const std::string& path);
        ~HandleUpload();

        void			setUpload(const std::string& path);
        void			setInput(const std::string& str);
        void			setFile(const std::string& file);

        std::string		getUpload() const;
        std::string		getInput() const;
        std::string		getFile() const;

        bool			save();
};
