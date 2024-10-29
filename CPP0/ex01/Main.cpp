/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:47:14 by emy               #+#    #+#             */
/*   Updated: 2024/10/28 15:40:00 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    PhoneBook phoneBook;
    std::string command;
    (void)argv;
    if (argc == 1)
    {
        while (true)
        {
            std::cout << "Enter a command (ADD, SEARCH, EXIT): ";
            std::getline(std::cin, command);
            if (command == "ADD")
                phoneBook.addContact();
            else if (command == "SEARCH")
                phoneBook.searchContact();
            else if (command == "EXIT")
            {
                std::cout << "Exiting the program." << std::endl;
                break;
            }
            else
                std::cout << "Invalid command. Please try again." << std::endl;
        }
        
    }
    else
		std::cout << "* TOO MANY ARGUMENTS *\n";
    return 0;
}
