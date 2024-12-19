/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:47:04 by estosche          #+#    #+#             */
/*   Updated: 2024/12/17 13:44:04 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

int main() {

	std::cout << color << "\n---Testing with main of subject---\n" << resetcolor << std::endl;

	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	mstack.pop();
	std::cout << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
	std::cout << *it << std::endl;
	++it;
	}
	std::stack<int> s(mstack);

	std::cout << color << "\n---Testing with std::deque---\n" << resetcolor << std::endl;
	MutantStack<int, std::deque<int> > mstack_deque;
	mstack_deque.push(5);
	mstack_deque.push(17);
	std::cout << "Top: " << mstack_deque.top() << std::endl;
	mstack_deque.pop();
	std::cout << "Size after pop: " << mstack_deque.size() << std::endl;

	mstack_deque.push(3);
	mstack_deque.push(5);
	mstack_deque.push(737);
	mstack_deque.push(0);

	std::cout << "Iterating over std::deque:" << std::endl;
	for (MutantStack<int, std::deque<int> >::iterator it = mstack_deque.begin(); it != mstack_deque.end(); ++it) {
		std::cout << *it << std::endl;
	}

	std::stack<int, std::deque<int> > s_deque(mstack_deque);
	std::cout << "Stack created from MutantStack with std::deque size: " << s_deque.size() << std::endl;

	std::cout << color << "\n---Testing with std::list---\n" << resetcolor << std::endl;
	MutantStack<int, std::list<int> > mstack_list;
	mstack_list.push(5);
	mstack_list.push(17);
	std::cout << "Top: " << mstack_list.top() << std::endl;
	mstack_list.pop();
	std::cout << "Size after pop: " << mstack_list.size() << std::endl;

	mstack_list.push(3);
	mstack_list.push(5);
	mstack_list.push(737);
	mstack_list.push(0);

	std::cout << "Iterating over std::list:" << std::endl;
	for (MutantStack<int, std::list<int> >::iterator it = mstack_list.begin(); it != mstack_list.end(); ++it) {
		std::cout << *it << std::endl;
	}

	std::stack<int, std::list<int> > s_list(mstack_list);
	std::cout << "Stack created from MutantStack with std::list size: " << s_list.size() << std::endl;

	return 0;
}