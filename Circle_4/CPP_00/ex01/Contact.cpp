/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:43:06 by viny              #+#    #+#             */
/*   Updated: 2025/08/11 20:45:02 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include <ctype.h>

/*Je creer la fonction du constructeur nommee contact de la class contact*/
Contact::Contact(void) 
: _first_name(), _last_name(), _nickname(), _phone_number(), _darkest_secret() {

    return;
}

/*Je creer la fonction du destructeur nommee contact de la class contact*/
Contact::~Contact(void) {

    return ;
}

//--------Getters-----------
std::string Contact::getFirstName() const {
    return (_first_name);
}

std::string Contact::getLastName() const {
    return (_last_name);
}

std::string Contact::getNickName() const {
    return (_nickname);
}

std::string Contact::getPhoneNumber() const {
    return (_phone_number);
}

std::string Contact::getDarkestSecret() const {
    return (_darkest_secret);
}

//----------Helpers----------
bool    Contact::isAlphaString(const std::string &s) const
{
    for (std::string::size_type i = 0; i < s.length(); i++) {
        unsigned char c = static_cast<unsigned char>(s[i]);
        if (!std::isalpha(c) && c != ' ')
            return (false);
    }
    return (true);
}

bool    Contact::isPhoneString(const std::string &s) const
{
    for (std::string::size_type i = 0; i < s.length(); i++) {
        char c = s[i];
        if (!std::isdigit(static_cast<unsigned char>(c)))
            return (false);
    }
    return (true);
}

//----------Setters---------
bool   Contact::setFirstName(const std::string &fn)
{
    if (fn.empty()) {
        std::cout << "Erreur : chaine vide.\n";
        return (false);
    }
    if (!isAlphaString(fn)) {
        std::cout << "Erreur : Contient des caracteres non autorisés.\n";
        return (false);
    }
    std::string tmp = fn;
    if (tmp.length() > MAX_NAME_LEN)
        std::cout << "Attention : First Name tronqué à 10 caractères.\n";
    _first_name = tmp;
    return (true);
}

bool   Contact::setLastName(const std::string &ln)
{
    if (ln.empty()) {
        std::cout << "Erreur : chaine vide.\n";
        return (false);
    }
    if (!isAlphaString(ln)) {
        std::cout << "Erreur : Contient des caracteres non autorisés.\n";
        return (false);
    }
    std::string tmp = ln;
    if (tmp.length() > MAX_NAME_LEN)
        std::cout << "Attention : Last name tronqué à 10 caractères.\n";
    _last_name = tmp;
    return (true);
}

bool   Contact::setNickName(const std::string &nn)
{
    if (nn.empty()) {
        std::cout << "Erreur : chaine vide.\n";
        return (false);
    }
    std::string tmp = nn;
    if (tmp.length() > MAX_NAME_LEN)
        std::cout << "Attention : Nickname tronqué à 10 caractères.\n";
    _nickname = tmp;
    return (true);
}

bool   Contact::setPhoneNumber(const std::string &pn)
{
    if (pn.empty()) {
        std::cout << "Erreur : chaine vide.\n";
        return (false);
    }
    if (!isPhoneString(pn)) {
        std::cout << "Erreur : Contient des caracteres non autorisés.\n";
        return (false);
    }
    std::string tmp = pn;
    if (tmp.length() > MAX_PHONE_LEN) {
        std::cout << "Attention : Phone number ne peut avoir que 15 caractères.\n";
        return (false);
    }
    _phone_number = tmp;
    return (true);
}

bool   Contact::setDarkestSecret(const std::string &ds)
{
    if (ds.empty()) {
        std::cout << "Erreur : chaine vide.\n";
        return (false);
    }
    std::string tmp = ds;
    if (tmp.length() > MAX_SECRET_LEN) {
        std::cout << "Attention : DarkestSecret ne peut avoir que 20 caractères.\n";
        return (false);
    }
    _darkest_secret = tmp;
    return (true); 
}
