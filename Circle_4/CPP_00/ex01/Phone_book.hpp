/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phone_book.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:19:13 by viny              #+#    #+#             */
/*   Updated: 2025/08/12 16:38:53 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Contact.hpp"

class Phone_Book {

    public :
    
        Phone_Book(void);
        ~Phone_Book(void);
        
        bool    printBook(void) const;
        void    addContact(Contact &c);
        bool    print_detail(int index) const;
        bool    IsValidIndex(int index) const;
        
        private :
        
        Contact _contact[8];
        int     _next_index;
        int     _size;
};

#endif