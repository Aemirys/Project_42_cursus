/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:13:08 by estosche          #+#    #+#             */
/*   Updated: 2024/12/02 15:27:30 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
#define CURE_HPP

#include "AMateria.hpp"

class Cure : public AMateria {
	
	public:
		Cure();
		Cure(Cure const & other);
   		Cure & operator=(Cure const & other);
		~Cure();

		AMateria* clone() const;
		void use(ICharacter& target);
};

#endif