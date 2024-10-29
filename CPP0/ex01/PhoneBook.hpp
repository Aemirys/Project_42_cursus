/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:49:12 by emy               #+#    #+#             */
/*   Updated: 2024/10/28 16:13:37 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
    public:
        PhoneBook();

        void addContact();
        void searchContact() const;
        void displayContact(int index) const;

    private:
        static const int maxContacts = 8;
        Contact contacts[maxContacts];
        int contactCount;
        int oldestIndex;

    std::string formatOutput(std::string str) const;
};

#endif

