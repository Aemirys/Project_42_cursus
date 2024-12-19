/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:26:32 by estosche          #+#    #+#             */
/*   Updated: 2024/12/16 15:31:54 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
#define EASYFIND_HPP
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#define color "\033[1;3;38;5;125m"
#define resetcolor "\033[0m"

class ElementNotFoundException :public std::exception {
	public:
		const char* what() const throw() {
			return ("Element not found");
		}
};

template<typename T>
typename T::iterator easyfind(T& container, int value) {
	typename T::iterator it = std::find(container.begin(), container.end(), value);
	if(it != container.end())
		return it;
	else
		throw ElementNotFoundException();
	
}

#endif