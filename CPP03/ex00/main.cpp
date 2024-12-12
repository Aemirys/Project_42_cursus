/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:04:54 by estosche          #+#    #+#             */
/*   Updated: 2024/11/26 13:05:23 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main() {

	ClapTrap clap("Tedd");
	
	clap.life();
	clap.attack("Target 1");
	clap.takeDamage(9);
	clap.life();
	clap.beRepaired(1);
	clap.life();

	return 0;
}