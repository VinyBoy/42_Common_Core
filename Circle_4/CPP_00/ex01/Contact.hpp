/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:42:14 by viny              #+#    #+#             */
/*   Updated: 2025/08/11 20:27:56 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <cctype>

class Contact {

    public :
    
        static const size_t MAX_NAME_LEN = 10;
        static const size_t MAX_SECRET_LEN = 20;
        static const size_t MAX_PHONE_LEN = 15;

        Contact(void);
        ~Contact(void);

        // Getters
        std::string getFirstName() const;
        std::string getLastName() const;
        std::string getNickName() const;
        std::string getPhoneNumber() const;
        std::string getDarkestSecret() const;

        //Setters
        bool setFirstName(const std::string &fn);
        bool setLastName(const std::string &ln);
        bool setNickName(const std::string &nn);
        bool setPhoneNumber(const std::string &pn);
        bool setDarkestSecret(const std::string &ds);
        
    private :
    
        std::string _first_name;
        std::string _last_name;
        std::string _nickname;
        std::string _phone_number;
        std::string _darkest_secret;

        //Helpers
        bool isAlphaString(const std::string &s) const;
        bool isPhoneString(const std::string &s) const;
    };


#endif 