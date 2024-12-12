/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:48:33 by estosche          #+#    #+#             */
/*   Updated: 2024/10/30 16:28:44 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Replace.hpp"

int main ( int argc, char ** argv) {

    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
        return 1;
    }

    Replace replacer(argv[1], argv[2], argv[3]);
    if (replacer.replaceAndWrite())
        std::cout << "Replacement completed successfully." << std::endl;
    else
        std::cerr << "Replacement failed." << std::endl;
    return (0);
}