/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:46:55 by emy               #+#    #+#             */
/*   Updated: 2024/10/28 16:15:38 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <limits>

PhoneBook::PhoneBook() : contactCount(0), oldestIndex(0) {}

void PhoneBook::addContact()
{
    std::string firstName, lastName, nickname, phoneNumber, darkestSecret;

    std::cout << "Enter first name: ";
    std::getline(std::cin, firstName);
    std::cout << "Enter last name: ";
    std::getline(std::cin, lastName);
    std::cout << "Enter nickname: ";
    std::getline(std::cin, nickname);
    std::cout << "Enter phone number: ";
    std::getline(std::cin, phoneNumber);
    std::cout << "Enter darkest secret: ";
    std::getline(std::cin, darkestSecret);

    if (firstName.empty() || lastName.empty() || nickname.empty() || phoneNumber.empty() || darkestSecret.empty())
    {
        std::cout << "Error: All fields must be filled." << std::endl;
        return;
    }
    if (contactCount < maxContacts)
    {
        contacts[contactCount].setContact(firstName, lastName, nickname, phoneNumber, darkestSecret);
        contactCount++;
    }
    else
    {
        contacts[oldestIndex].setContact(firstName, lastName, nickname, phoneNumber, darkestSecret);
        oldestIndex = (oldestIndex + 1) % maxContacts;
    }
    std::cout << "Contact added successfully!" << std::endl;
}

void PhoneBook::searchContact() const
{
    if (contactCount == 0)
    {
        std::cout << "PhoneBook is empty!" << std::endl;
        return;
    }
    std::cout << std::setw(10) << "Index" << "|" 
              << std::setw(10) << "First Name" << "|" 
              << std::setw(10) << "Last Name" << "|" 
              << std::setw(10) << "Nickname" << "|" << std::endl;
    for (int i = 0; i < contactCount; i++)
    {
        std::cout << std::setw(10) << i + 1 << "|"
                  << std::setw(10) << formatOutput(contacts[i].getFirstName()) << "|"
                  << std::setw(10) << formatOutput(contacts[i].getLastName()) << "|"
                  << std::setw(10) << formatOutput(contacts[i].getNickname()) << "|" << std::endl;
    }

    int index;
    std::cout << "Enter the index of the contact to display: ";
    if (!(std::cin >> index) || index < 1 || index > contactCount)
    {
        std::cout << "Invalid index!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    else
    {
        displayContact(index - 1);
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void PhoneBook::displayContact(int index) const
{
    const Contact& contact = contacts[index];
    std::cout << "First Name: " << contact.getFirstName() << std::endl;
    std::cout << "Last Name: " << contact.getLastName() << std::endl;
    std::cout << "Nickname: " << contact.getNickname() << std::endl;
    std::cout << "Phone Number: " << contact.getPhoneNumber() << std::endl;
    std::cout << "Darkest Secret: " << contact.getDarkestSecret() << std::endl;
}

std::string PhoneBook::formatOutput(std::string str) const
{
    if (str.length() > 10)
    {
        str = str.substr(0, 9) + ".";
    }
    return str;
}
