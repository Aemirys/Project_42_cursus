/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:19:08 by estosche          #+#    #+#             */
/*   Updated: 2024/10/30 12:54:28 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
    int N = 5;
    Zombie* horde = zombieHorde(N, "Walker");
    if (horde != NULL)
    {
        for (int i = 0; i < N; ++i)
            horde[i].announce();
      delete[] horde;
    }
    else
        return (1);
    return 0;
}