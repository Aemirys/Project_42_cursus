/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:34:31 by estosche          #+#    #+#             */
/*   Updated: 2024/10/30 12:53:54 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name) {
    if (N <= 0)
        return NULL;
    Zombie* horde = new Zombie[N];
    if (!horde)
    {
        std::cout << "Memory Allocation Failled" << std::endl;
        return (NULL);
    }
    for (int i = 0; i < N; ++i) {
        new (&horde[i]) Zombie(name, i + 1);
    }

    return horde;
}