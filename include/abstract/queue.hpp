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
    Abstract Data Structure: Queue
*/

template<typename T>
class Queue : public IDataStructure {
private:
	ISequence<T>* m_pImpl;

public:
    // constructor, allow manual init alloc size
    Queue(ISequence<T>* _pImpl) {
		assert(_pImpl != nullptr && "Can't create queue with no implementation");
        m_pImpl = _pImpl;
    }

    // destructor
    ~Queue() {
        delete m_pImpl;
    }

    // get number of elements in queue
    size_t size() override {
		return m_pImpl->size();
    }

	// get allocated size of queue
	size_t allocated() override {
		return m_pImpl->allocated() + sizeof(Queue);
	}

    // check if queue is empty
    bool empty() override {
        return m_pImpl->empty();
    }

    // push element to back of queue
    void enqueue(T _elem) override {
        m_pImpl->push_back(_elem);
    }

    // pop element from front queue
    T dequeue() override {
		if (this->empty()) {
			throw std::out_of_range("Cannot dequeue from empty queue");
		}
        return m_pImpl->pop_front();
    }

    // get a reference to front element
    T& front() override {
		if (this->empty()) {
			throw std::out_of_range("Cannot get front of empty queue");
		}
        return m_pImpl->operator[](0);
    }

    // get a reference to back element
    T& back() override {
        if (this->empty()) {
            throw std::out_of_range("Cannot get back of empty queue");
        }
        return m_pImpl->operator[](this->size() - 1);
    }

	// convert to string
    std::string toString() override  {
        return m_pImpl->toString();
    }

};
