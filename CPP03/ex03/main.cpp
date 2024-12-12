/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:04:54 by estosche          #+#    #+#             */
/*   Updated: 2024/11/27 11:05:41 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

int main() {
    // Test construction and destruction
    std::cout << "=== Test DiamondTrap Construction and Destruction ===\n";
    {
        DiamondTrap diamond("Shiny");
    }
    std::cout << "\n";

    // Test attack
    std::cout << "=== Test DiamondTrap Attack ===\n";
    DiamondTrap diamond("Glitter");
    diamond.attack("Enemy");

    // Test special abilities
    std::cout << "\n=== Test DiamondTrap Special Abilities ===\n";
    diamond.guardGate();  // From ScavTrap
    diamond.highFivesGuys(); // From FragTrap
    diamond.whoAmI();    // Unique to DiamondTrap

    // Test copy constructor
    std::cout << "\n=== Test DiamondTrap Copy Constructor ===\n";
    DiamondTrap diamondCopy(diamond);

    // Test assignment operator
    std::cout << "\n=== Test DiamondTrap Assignment Operator ===\n";
    DiamondTrap diamondAssigned("Placeholder");
    diamondAssigned = diamond;

    std::cout << "\n=== End of Tests ===\n";

    return 0;
}