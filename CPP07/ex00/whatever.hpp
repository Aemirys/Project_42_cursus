/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:15:06 by estosche          #+#    #+#             */
/*   Updated: 2024/12/16 13:38:55 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
#define WHATEVER_HPP
#define color "\033[1;3;38;5;125m"
#define resetcolor "\033[0m"
#include <iostream>

template <typename T>
void swap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

template <typename T>
T min(const T& a, const T& b){
	return (a < b) ? a : b;
}

template <typename T>
T max(const T& a, const T& b) {
	return (a > b) ? a : b;
}

#endif