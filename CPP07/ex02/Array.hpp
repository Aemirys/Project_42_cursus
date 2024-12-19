/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:46:57 by estosche          #+#    #+#             */
/*   Updated: 2024/12/17 09:57:24 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#define color "\033[1;3;38;5;125m"
#define resetcolor "\033[0m"

#include <iostream>
#include <stdexcept>

template <typename T>
class Array {
  private:
	T* _elements;
	unsigned int _size;
  public:
	Array() : _elements(NULL), _size(0) {
		std::cout << "Default constructed." << std::endl;
	}
	Array(unsigned int n) : _elements(new T[n]()), _size(n) {
		std::cout << "Size constructed with size = " << _size << "." << std::endl;
	}
	Array(const Array& other) : _elements(new T[other._size]), _size(other._size){
		std::cout << "Array copied with size = " << _size << "." << std::endl;
		for(unsigned int i = 0; i < _size; i++) {
			_elements[i] = other._elements[i];
		}
	}

	Array& operator=(const Array& other) {
		
		if(this != &other) {
			delete[] _elements;
			_size = other._size;
			_elements = new T[_size];
			for (unsigned int i = 0; i < _size; i++) {
				_elements[i] = other._elements[i];
			}
		}
		std::cout << "Array assigned with size = " << _size << "." << std::endl;
		return *this;
	}

	~Array() {
		std::cout << "Array destroyed with size = " << _size << "." << std::endl;
		delete[] _elements;
	}
	
	T& operator[](unsigned int index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of bounds");
        }
        return _elements[index];
    }

	const T& operator[](unsigned int index) const {
		if (index >= _size) {
			throw std::out_of_range("Index out of bounds");
		}
		return _elements[index];
	}
	
	unsigned int size() const {
		return _size;
	}
};

#endif