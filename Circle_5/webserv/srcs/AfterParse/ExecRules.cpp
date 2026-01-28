/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecRules.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:49:29 by caspar            #+#    #+#             */
/*   Updated: 2025/10/22 13:00:06 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/AfterParse/ExecRules.hpp"

ExecRules::ExecRules() : _redirect_code(0), _has_redirect(false) {}

ExecRules::ExecRules(const std::string &path) : _redirect_code(0), _has_redirect(false) {
	this->_path = path;
}

ExecRules::~ExecRules() {}

void ExecRules::setPath(const std::string &path) {
	_path = path;
}

void ExecRules::setRoot(const std::string &root) {
	_root = root;
}

void ExecRules::setIndex(const std::string &index) {
	_index = index;
}

void ExecRules::setCgi(const std::string &cgi) {
	_cgi = cgi;
}

void ExecRules::setUpload(const std::string &upload) {
	_upload_path = upload;
}

void ExecRules::addMethod(const std::string &method) {
	_methods.push_back(method);
}

void ExecRules::setRedirect(int code, const std::string &url) {
	_redirect_code = code;
	_redirect_url = url;
	_has_redirect = true;
}

void ExecRules::clearRedirect() {
	_redirect_code = 0;
	_redirect_url = "";
	_has_redirect = false;
}

std::string ExecRules::getPath() const {
	return (_path);
}

std::string ExecRules::getRoot() const {
	return (_root);
}

std::string ExecRules::getIndex() const {
	return (_index);
}

std::string ExecRules::getCgi() const { 
	return (_cgi);
}

std::string ExecRules::getUpload() const {
	return (_upload_path);
}

std::vector<std::string> ExecRules::getMethods() const {
	return (_methods);
}

bool ExecRules::hasRedirect() const {
	return (_has_redirect);
}

int ExecRules::getRedirectCode() const {
	return (_redirect_code);
}

std::string ExecRules::getRedirectUrl() const {
	return (_redirect_url);
}

bool ExecRules::isMethodAllowed(const std::string &method) const {
	for (std::vector<std::string>::const_iterator ite = _methods.begin();
			 ite != _methods.end(); ++ite) {
		if (*ite == method)
			return (true);
	}
	return (false);
}
