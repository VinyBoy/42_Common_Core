/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecRules.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caspar <caspar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:49:23 by caspar            #+#    #+#             */
/*   Updated: 2025/11/20 17:39:54 by caspar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>

class ExecRules {
    private:
        std::string _path;
        std::string _root;
        std::vector<std::string> _methods;
        std::string _index;
        std::string _cgi;
        std::string _upload_path;
        std::string _redirect_url;
        int _redirect_code;
        bool _has_redirect;

    public:
        ExecRules();
        ExecRules(const std::string &path);
        ~ExecRules();

        void setPath(const std::string &path);
        void setRoot(const std::string &root);
        void setIndex(const std::string &index);
        void setCgi(const std::string &cgi);
        void setUpload(const std::string &upload);
        void addMethod(const std::string &method);
        void setRedirect(int code, const std::string &url);
        void clearRedirect();

        std::string getPath() const;
        std::string getRoot() const;
        std::string getIndex() const;
        std::string getCgi() const;
        std::string getUpload() const;
        std::vector<std::string> getMethods() const;
        bool hasRedirect() const;
        int getRedirectCode() const;
        std::string getRedirectUrl() const;

        bool isMethodAllowed(const std::string &method) const;
};
