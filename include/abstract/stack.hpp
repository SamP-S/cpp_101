#pragma once

// std lib
#include <exception>
#include <sstream>
#include <cassert>
// internal
#include "i_data_structure.hpp"
#include "sequence/i_sequence.hpp"

/*
	Abstract Data Structure: Stack
*/

template<typename T>
class Stack : public IDataStructure<T> {
private:
	ISequence<T>* m_pImpl;

public:
	// constructor, allow manual init alloc size
	Stack(ISequence<T>* _pImpl) {
		assert(_pImpl != nullptr && "Can't create stack with no implementation");
		m_pImpl = _pImpl;
	}

	// destructor
	~Stack() {
		delete m_pImpl;
	}

	// get number of elements in stack
	size_t size() override {
		return m_pImpl->size();
	}

	// get allocated size of stack
	size_t allocated() override {
		return m_pImpl->allocated() + sizeof(Stack);
	}

	// check if stack is empty
	bool empty() override {
		return m_pImpl->empty();
	}

	// push element to top of stack
	void push(T _elem) override {
		m_pImpl->push_back(_elem);
	}

	// pop element from top of stack
	T pop() override {
		if (this->empty()) {
			throw std::out_of_range("Cannot pop from empty stack");
		}
		return m_pImpl->pop_back();
	}

	// get a reference to top element
	T& top() override {
		if (this->empty()) {
			throw std::out_of_range("Cannot get top of empty stack");
		}
		return m_pImpl->operator[](this->size() - 1);
	}

	// convert to string
	std::string toString() override {
		return m_pImpl->toString();
	}
};
