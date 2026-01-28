/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phone_book.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:19:22 by viny              #+#    #+#             */
/*   Updated: 2025/08/12 16:39:37 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phone_book.hpp"

Phone_Book::Phone_Book(void) : _next_index(0), _size(0){}
Phone_Book::~Phone_Book(void) {}

void Phone_Book::addContact(Contact &newContact)
{
  std::string new_cmd;     
  std::cout << "Enter first name\n";
  //First name
	while(std::getline(std::cin, new_cmd))
	{
    const std::string tmp = new_cmd;
    if (newContact.setFirstName(tmp))
    	break;
    else
    	std::cout << "Bad first name ❌. Rewrite please\n";
  }
  std::cout << "Enter last name\n";
  //Last name
  while(std::getline(std::cin, new_cmd))
  {
		const std::string tmp = new_cmd;
		if (newContact.setLastName(tmp))
			break;
		else
			std::cout << "Bad last name ❌. Rewrite please\n";
  }
  std::cout << "Enter nick name\n";
  //Nick name
  while(std::getline(std::cin, new_cmd))
  {
		const std::string tmp = new_cmd;
		if (newContact.setNickName(tmp))
			break;
		else
			std::cout << "Bad Nick name ❌. Rewrite please\n";
  }
  std::cout << "Enter phone number\n";
  //Phone number name
  while(std::getline(std::cin, new_cmd))
  {
		const std::string tmp = new_cmd;
		if (newContact.setPhoneNumber(tmp))
			break;
		else
			std::cout << "Bad phone number ❌. Rewrite please\n";
  }
  std::cout << "Enter darkest secret\n";
  //Darkest secret
  while(std::getline(std::cin, new_cmd))
  {
		const std::string tmp = new_cmd;
		if (newContact.setDarkestSecret(tmp))
			break;
		else
			std::cout << "Bad Darkest secret ❌. Rewrite please\n";
  }
  // copie circulaire
  _contact[_next_index] = newContact;
  if (_size < 8)
  	++_size;
  _next_index = (_next_index + 1) % 8;
  std::cout << "Contact Added✅\n" << std::endl;
  return ;
}

static std::string	FormatCellTen(const std::string &s) {

	if (s.length() > 10)
		return (s.substr(0, 9) + ".");
	return (s);
}

bool Phone_Book::printBook() const
{
	std::string cmd;
	if (_size == 0) {
		std::cout << "Phone_Book is empty. Please Add contact\n" << std::endl;
		return (false);
	}
	std::cout << "┌───────────────────────────────────────────┐\n";
	std::cout << "│" << std::setw(10) << "Index " << "│" \
	<< std::setw(10) << "First Name" << "│" \
	<< std::setw(10) << "Last Name" << "│" \
	<< std::setw(10) << " Nickname " << "│" \
	<< '\n';
	std::cout << "│───────────────────────────────────────────│\n";

	for (int i = 0; i < 8; i++)
	{
	std::cout << "│" << std::setw(10) << i << "│" \
	<< std::setw(10) << FormatCellTen(_contact[i].getFirstName()) << "│" \
	<< std::setw(10) <<  FormatCellTen(_contact[i].getLastName()) << "│" \
	<< std::setw(10) <<  FormatCellTen(_contact[i].getNickName()) << "│" \
	<< '\n';
	if (i == 7 )
		std::cout << "└───────────────────────────────────────────┘\n";
	else
		std::cout << "│───────────────────────────────────────────│\n";
	}
	return (true);
}

bool    Phone_Book::print_detail(int index) const
{
    if (index < 0 || index >= _size) {
        std::cout << "Index invalide.\n";
        return (false);
    }
    const Contact &c = _contact[index];
    std::cout << "First name: " << c.getFirstName() << std::endl;
    std::cout << "Last name: " << c.getLastName() << std::endl;
    std::cout << "Nickname: " << c.getNickName() << std::endl;
    std::cout << "Phone number: " << c.getPhoneNumber() << std::endl;
    std::cout << "Darkest secret: " << c.getDarkestSecret() << std::endl;
	std::cout << std::endl;
    return (true);
}

bool    Phone_Book::IsValidIndex(int index) const { 
	return (index >= 0 && index < _size);
}
