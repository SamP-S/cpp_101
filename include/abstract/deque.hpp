#pragma once

// std lib
#include <exception>
#include <cstring>
#include <sstream>
#include <cassert>
// internal
#include "i_data_structure.hpp"
#include "sequence/i_sequence.hpp"

/*
	Abstract Data Structure: Deque
*/

template<typename T>
class Deque : public IDataStructure {
private:
	ISequence<T>* m_pImpl;

public:
	// constructor, allow manual init alloc size
	Deque(ISequence<T>* _pImpl) {
		assert(_pImpl != nullptr && "Can't create deque with no implementation");
		m_pImpl = _pImpl;
	}

	// destructor
	~Deque() {
		delete m_pImpl;
	}

	// get number of elements in deque
	size_t size() override {
		return m_pImpl->size();
	}

	// get allocated size of deque
	size_t allocated() override {
		return m_pImpl->allocated() + sizeof(Deque);
	}

	// check if deque is empty
	bool empty() override {
		return m_pImpl->empty();
	}

	// push element to front of deque
	void push_front(T _elem) override {
		m_pImpl->push_front(_elem);
	}

	// pop element from front of deque
	T pop_front() override {
		if (this->empty()) {
			throw std::out_of_range("Cannot pop front from empty deque");
		}
		return m_pImpl->pop_front();
	}

	// push element to back of deque
	void push_back(T _elem) override {
		m_pImpl->push_back(_elem);
	}

	// pop element from back of deque
	T pop_back() override {
		if (this->empty()) {
			throw std::out_of_range("Cannot pop back from empty deque");
		}
		return m_pImpl->pop_back();
	}

	// get a reference to front element
	T& front() override {
		if (this->empty()) {
			throw std::out_of_range("Cannot get front of empty deque");
		}
		return m_pImpl->operator[](0);
	}

	// get a reference to back element
	T& back() override {
		if (this->empty()) {
			throw std::out_of_range("Cannot get back of empty deque");
		}
		return m_pImpl->operator[](this->size() - 1);
	}

	// convert to string
	std::string toString() override {
		return m_pImpl->toString();
	}
};