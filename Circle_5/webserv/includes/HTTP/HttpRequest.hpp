/* ************************************************************************** */
/*																																						*/
/*																												:::
 * ::::::::	 */
/*	 HttpRequest.hpp
 * :+:			:+:		:+:	 */
/*																										+:+
 * +:+				 +:+		 */
/*	 By: oztozdem <oztozdem@student.42.fr>
 * +#+	+:+			 +#+				*/
/*																								+#+#+#+#+#+
 * +#+					 */
/*	 Created: 2025/10/03 11:24:08 by oztozdem
 * #+#		#+#						 */
/*	 Updated: 2025/10/15 17:40:04 by oztozdem
 * ###	 ########.fr			 */
/*																																						*/
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>

class HttpRequest {
private:
  std::string _method;
  std::string _url;
  std::map<std::string, std::string> _headers;
  std::string _body;
  std::string _httpVersion;
  std::string _path;
  std::string _query;
  bool _complete;
  bool _valid;
  bool _isHTTPS;
  std::string _errorMessage;

public:
  HttpRequest();
  HttpRequest(const std::string &method, const std::string &url);
  ~HttpRequest();

  std::string getMethod() const;
  std::string getUrl() const;
  std::map<std::string, std::string> getHeaders() const;
  std::string getBody() const;
  std::string getHttpVersion() const;
  std::string getPath() const;
  std::string getQuery() const;

  std::string getHeader(const std::string &key) const;
  std::string getPort() const;

  void setMethod(const std::string &method);
  void setUrl(const std::string &url);
  void setPathAndQuery(const std::string &url);
  void setHttpVersion(const std::string &version);
  void addHeader(const std::string &key, const std::string &value);
  void setBody(const std::string &body);
  void setComplete(bool complete);
  void setValid(bool valid);

  bool isComplete() const;
  bool isValid() const;
  bool isHTTPS() const;
  std::string getErrorMessage() const;
  std::string toString() const;

  static HttpRequest parseHttpRequest(const std::string &rawRequest);
};
