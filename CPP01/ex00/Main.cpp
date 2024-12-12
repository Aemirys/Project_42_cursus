/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:21:57 by estosche          #+#    #+#             */
/*   Updated: 2024/10/30 11:02:59 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main() {
    Zombie* heapZombie = newZombie("Alphonse");
    if (heapZombie == NULL)
    {
        std::cout << "Memory Allocation Failled" << std::endl;
        return (0);
    }
    heapZombie->announce();
    delete heapZombie;

    randomChump("Gerard");
    
    return (0);
}