/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:57:15 by estosche          #+#    #+#             */
/*   Updated: 2024/10/30 14:02:53 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main()
{
    std::string str = "HI THIS IS BRAIN";
    std::string* stringPTR = &str;
    std::string& stringREF = str;

    std::cout << "Memory adress of str : " << &str << std::endl;
    std::cout << "Memory adress of stringPTR : " << stringPTR << std::endl;
    std::cout << "Memory adress of stringREF : " << &stringREF << std::endl;

    std::cout << "Value of str : " << str << std::endl;
    std::cout << "Value of stringPTR : " << *stringPTR << std::endl;
    std::cout << "Value of stringREF : " << stringREF << std::endl;

    return (0);
}