/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:41:45 by oztozdem          #+#    #+#             */
/*   Updated: 2025/10/15 17:41:46 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>

class HttpResponse {
    private:
        int _statusCode;
        std::string _statusMessage;
        std::map<std::string, std::string> _headers;
        std::string _body;

        static std::string intToString(int n);
    public:
        HttpResponse();
        ~HttpResponse();

        void setStatus(int code, const std::string& message);
        void setHeader(const std::string& key, const std::string& value);
        void setBody(const std::string& body);
        std::string toString() const;
        
        int getStatusCode() const;
        std::string getBody() const;
        std::map<std::string, std::string> getHeaders() const;

        static bool fileExists(const std::string& path);
		static std::string readFile(const std::string& path);
};
