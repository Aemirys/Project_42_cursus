/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:48:37 by estosche          #+#    #+#             */
/*   Updated: 2024/12/17 13:44:32 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

# include <iostream>
# include <algorithm>
# include <string>
# include <stack>
# include <list>
# include <vector>
# include <deque>

#define color "\033[1;3;38;5;125m"
#define resetcolor "\033[0m"

template <typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container> {
	public:

	MutantStack() : std::stack<T, Container>() {}
	MutantStack(const MutantStack& other) : std::stack<T, Container>(other) {}
	MutantStack &operator=(const MutantStack& other) {
		std::stack<T>::operator=(other);
		return *this;
	}

	~MutantStack() {};

	typedef typename Container::iterator iterator;
	typedef typename Container::const_iterator const_iterator;

	void push(const T& value) {
		this->c.push_back(value);
	}

	iterator begin() {
		return this->c.begin();
	}

	iterator end() {
		return this->c.end();
	}
};

#endif