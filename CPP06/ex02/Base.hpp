/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:23:24 by estosche          #+#    #+#             */
/*   Updated: 2024/12/12 15:05:24 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
#define BASE_HPP

#define color "\033[1;3;38;5;125m"
#define resetcolor "\033[0m"

#include <iostream>
#include <cstdlib>
#include <ctime>


class Base
{
	public:
		virtual ~Base();
		
};

class A : public Base {};
class B : public Base {};
class C : public Base {};
Base* generate();
void identify(Base* p);
void identify(Base& p);

#endif