/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:04:54 by estosche          #+#    #+#             */
/*   Updated: 2024/11/27 11:02:34 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main() {
    // Test construction and destruction
    std::cout << "=== Test FragTrap Construction and Destruction ===\n";
    {
        FragTrap frag("Hero");
    }
    std::cout << "\n";

    // Test attack
    std::cout << "=== Test FragTrap Attack ===\n";
    FragTrap frag("Warrior");
    frag.attack("Enemy");

    // Test high five
    std::cout << "\n=== Test FragTrap High Five ===\n";
    frag.highFivesGuys();

    // Test copy constructor
    std::cout << "\n=== Test FragTrap Copy Constructor ===\n";
    FragTrap fragCopy(frag);

    // Test assignment operator
    std::cout << "\n=== Test FragTrap Assignment Operator ===\n";
    FragTrap fragAssigned("Placeholder");
    fragAssigned = frag;

    std::cout << "\n=== End of Tests ===\n";

    return 0;
}