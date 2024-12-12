/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:09:21 by estosche          #+#    #+#             */
/*   Updated: 2024/10/30 12:41:25 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>
#include <iostream>

class Zombie
{
    private:
        std::string name;
        int number;
    public:
        Zombie();
        Zombie(std::string name, int number);
        ~Zombie();
        void announce() const;
       // void setName(std::string name);
};
Zombie* zombieHorde(int N, std::string name);

#endif