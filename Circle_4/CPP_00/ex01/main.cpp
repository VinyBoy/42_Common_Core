/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:17:47 by viny              #+#    #+#             */
/*   Updated: 2025/11/30 10:35:07 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phone_book.hpp"
#include "Contact.hpp"
#include "unistd.h"

static bool parseIndexStrict(const std::string &s, int &out)
{
    int v;
    std::istringstream iss(s);

    if (!(iss >> v))
        return (false);
    iss >> std::ws;
    std::char_traits<char>::int_type c;
    c = iss.peek();
    if (c != std::char_traits<char>::eof())
        return (false);
    out = v;
    return (true);
}

bool    AskAndPrintDetails(const Phone_Book &Repertoire)
{
    std::string line;
    int         index;

    index = -1;
    std::cout << "Wich index would you print ?\n>";
    if (!std::getline(std::cin, line))
        return (false);
    if (!parseIndexStrict(line, index) || !Repertoire.IsValidIndex(index)) {
        std::cout << "Index invalide ou hors bornes.\n";
        return (true);
    }
    Repertoire.print_detail(index);
    return (true);
}

int main(void)
{
    
    Phone_Book Repertoire;
    Contact Contact;
    std::string cmd;
    
    std::cout << "\n\n\n┌───────────────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│                                 PHONEBOOK                                 │\n";
    std::cout << "└───────────────────────────────────────────────────────────────────────────┘\n\n";
    std::cout << "1) ADD   " << "2) SEARCH   " << "3) EXIT\n\n" << "Choix> ";
    while (std::getline(std::cin, cmd))
    {
		if (std::cin.eof())
		{
    		std::cout << "\nFin de saisie (EOF).\n";
   		 	std::cin.clear();
    		return 1;
		}
        if (cmd =="ADD") {
            std::cout << std::endl;
            Repertoire.addContact(Contact);
        }
        else if (cmd =="SEARCH") {
            std::cout << std::endl;
            if (Repertoire.printBook())
            {   while (true)
                {
                    std::string answer;
                    std::cout << "Do you want to print details ? (Yes / No)\n>";
                    if (!std::getline(std::cin, answer))
                      return (0);
                    if (answer== "Yes") {
                        AskAndPrintDetails(Repertoire);
                        break ;
                    }
                    else if (answer == "No")
                        break ;
                    else
                        std::cout << "Error ❌. Please type Yes or No\n";
                }
            }
        }
        else if (cmd =="EXIT") {
            std::cout << std::endl;
            break;
        }
        else
            std::cout << "\nError ❌. Rewrite please.\n\nChoix> " << std::endl << std::endl;;
        std::cout << "1) ADD   " << "2) SEARCH   " << "3) EXIT\n\n" << "Choix> ";
    }
    return (0);
}
