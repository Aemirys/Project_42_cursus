/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:04:54 by estosche          #+#    #+#             */
/*   Updated: 2024/11/27 11:04:37 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"


int main() {
    // Test construction/destruction
    {
        std::cout << "=== Test ScavTrap Construction and Destruction ===\n";
        ScavTrap scav("Guardian");
    }
    std::cout << "\n";

    // Test attack
    std::cout << "=== Test ScavTrap Attack ===\n";
    ScavTrap scav("Fighter");
    scav.attack("Enemy");

    // Test guardGate
    std::cout << "\n=== Test ScavTrap Guard Gate ===\n";
    scav.guardGate();

    // Test copy constructor and assignment
    std::cout << "\n=== Test ScavTrap Copy ===\n";
    ScavTrap copyScav(scav);

    std::cout << "\n=== Test ScavTrap Assignment ===\n";
    ScavTrap assignedScav("Placeholder");
    assignedScav = scav;
    
    std::cout << "\n=== End of Tests ===\n";

    return 0;
}