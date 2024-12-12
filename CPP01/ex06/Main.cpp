/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:48:38 by estosche          #+#    #+#             */
/*   Updated: 2024/11/04 10:54:53 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main(int argc, char **argv){
    if (argc != 2){
        std::cerr << "Usage: " <<argv[0] << " <level>" << std::endl;
        return 1;
    }
    Harl harl;
    harl.complain(argv[1]);
    return 0;
}