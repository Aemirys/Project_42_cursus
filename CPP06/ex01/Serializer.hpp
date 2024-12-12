/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:28:54 by estosche          #+#    #+#             */
/*   Updated: 2024/12/12 15:13:07 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#define color "\033[1;3;38;5;125m"
#define resetcolor "\033[0m"
#include <iostream>

typedef unsigned long uintptr_t;

struct Data {
		int id;
		std::string name;
};

class Serializer {
	public:
		static uintptr_t serialize(Data* ptr);
		static Data*  deserialize(uintptr_t raw);
	private: 
		Serializer();
		Serializer(const Serializer& other);
		Serializer& operator=(const Serializer& other);
		~Serializer();
};

#endif