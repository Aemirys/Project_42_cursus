/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:24:31 by estosche          #+#    #+#             */
/*   Updated: 2024/12/16 13:38:43 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
#define ITER_HPP

#define color "\033[1;3;38;5;125m"
#define resetcolor "\033[0m"
#include <iostream>

template <typename T, typename F>
void iter(T* array, size_t lenght, F func) {
	for (size_t i = 0; i < lenght; i++) {
		func(array[i]);
	}       
}

#endif