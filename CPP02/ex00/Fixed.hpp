/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:38:54 by estosche          #+#    #+#             */
/*   Updated: 2024/11/14 13:18:32 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <string>
#include <iostream>

class Fixed {
	private:
		int	_num;
		static const int nbr = 8;
	
	public:
		Fixed ();
		Fixed(const Fixed &other);
		Fixed& operator=(const Fixed &other);
		~Fixed ();
		int	getRawBits(void) const;
		void	setRawBits(int const raw);
	
};

#endif
