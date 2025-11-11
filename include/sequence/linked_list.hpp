#pragma once

// std lib
#include <exception>
#include <cstring>
#include <sstream>
#include <cassert>
#include <iostream>
//internal
#include "common/global.hpp"
#include "sequence/i_sequence.hpp"

/*
    Data Structure: Linked List
*/
	
template<typename T>
class LinkedList : public ISequence<T> {
private: 
	
	struct LinkedNode {
		T data;
		LinkedNode* pNext;
	};

	LinkedNode* m_pFirst;
	size_t m_size;

public:
    // O(1): constructor
    LinkedList() {
		m_pFirst = nullptr;
		m_size = 0;
	} 
	
    // O(n): destructor
    ~LinkedList() {
		this->clear();
	}

    // O(1): get used size of dynamic array
    size_t size() override {
		return m_size;
	}

	// O(1): get allocated memory size of dynamic array
	size_t allocated() override {
		return m_size * sizeof(LinkedNode) + sizeof(LinkedList);
	}

	// O(1): check if used dynamic array is empty
	bool empty() override {
		return m_size == 0;
	}

	// O(n): remove all elements from array
    void clear() override {
		while (m_pFirst != nullptr) {
			this->pop_front();
		}
	}

    // O(n): fill all elements with value
    void fill(T _value) override {
		// iterate through list, set value
		LinkedNode* pNode = m_pFirst;
		while (pNode != nullptr) {
			pNode->data = _value;
			pNode = pNode->pNext;
		};
	}
    
    // O(n): overload index operator
    T& operator[](size_t _index) override {
		if (_index >= m_size) {
			throw std::out_of_range("Cannot access element out of range");
		}
		size_t i = 0;
		LinkedNode* pNode = m_pFirst;
		while (pNode != nullptr) {
			if (i == _index) {
				return pNode->data;
			}
			pNode = pNode->pNext;
			i++;
		}
	}

	// O(1): push front
	void push_front(T _elem) override {
		LinkedNode* pTmp = m_pFirst;
		LinkedNode* pFront = new LinkedNode();
		pFront->data = _elem;
		pFront->pNext = pTmp;
		m_pFirst = pFront;
		m_size++;
	}

	// O(1): pop front
	T pop_front() override {
		if (this->empty()) {
			throw std::out_of_range("Cannot pop from empty list");
		}
		LinkedNode* pTmp = m_pFirst;
		T ret = m_pFirst->data;
		m_pFirst = m_pFirst->pNext;
		m_size--;
		delete pTmp;
	}

	// O(n): push back
	void push_back(T _elem) override {
		// create new node
		LinkedNode* pNew = new LinkedNode();
		pNew->data = _elem;
		pNew->pNext = nullptr;
		// add to first if empty
		if (m_pFirst == nullptr) {
			m_pFirst = pNew;
			m_size++;
			return;
		}
		// find end and add node
		LinkedNode* pNode = m_pFirst;
		while (pNode->pNext != nullptr) {
			pNode = pNode->pNext;
		}
		pNode->pNext = pNew;
		m_size++;
	}

	// O(n): pop back
	T pop_back() override {
		if (this->empty()) {
			throw std::out_of_range("Cannot pop from empty list");
		}
		// remove from frist if size 1
		if (m_size == 1) {
			assert(m_pFirst->pNext == nullptr && "Size mismatch");
			delete m_pFirst;
			m_pFirst = nullptr;
			m_size--;
		}
		// find and remove end node
		LinkedNode* pNodeBefore = m_pFirst;
		LinkedNode* pNodeEnd = m_pFirst->pNext;
		while (pNodeEnd->pNext != nullptr) {
			pNodeBefore = pNodeEnd;
			pNodeEnd = pNodeEnd->pNext;
		}
		pNodeBefore->pNext = nullptr;
		delete pNodeEnd;
		m_size--;
	}

	// O(n): insert element at index
	void insert(size_t _index, T _elem) override {
		// clamp index to end of list
		if (_index >= m_size) {
			this->push_back(_elem);
			return;
		}
		// push front if index 0
		if (_index == 0) {
			this->push_front(_elem);
		}
		// find node at index
		LinkedNode* pNodeBefore = m_pFirst;
		LinkedNode* pNodeKey = m_pFirst->pNext;
		size_t i = 1;
		while (_index != i) {
			pNodeBefore = pNodeKey;
			pNodeKey = pNodeKey->pNext;
			i++;
		}
		// insert
		LinkedNode* pNew = new LinkedNode();
		pNew->data = _elem;
		pNew->pNext = pNodeKey;
		pNodeBefore->pNext = pNew;
		m_size++;
	}

	// O(n): remove element at index
	T remove(size_t _index) override {
		// remove from end if index >= size
		if (_index >= m_size) {
			return this->pop_back();
		}
		// pop front if index 0
		if (_index == 0) {
			return this->pop_front();
		}
		// find node at index
		LinkedNode* pNodeBefore = m_pFirst;
		LinkedNode* pNodeKey = m_pFirst->pNext;
		size_t i = 1;
		while (_index != i) {
			pNodeBefore = pNodeKey;
			pNodeKey = pNodeKey->pNext;
			i++;
		}
		T ret = pNodeKey->data;
		// remove
		pNodeBefore->pNext = pNodeKey->pNext;
		delete pNodeKey;
		m_size--;
		return ret;
	}

    // O(n): convert array to string
    std::string toString() override {
        std::stringstream ss;
      	ss << "{ size=" << m_size << "; alloc=" << this->allocated() << "; ";
		LinkedNode* pNode = m_pFirst;
		while (pNode != nullptr) {
			ss << pNode->data;
			if (pNode->pNext != nullptr) {
				ss << ", ";
			}
			pNode = pNode->pNext;
		}
        ss << " }";
        return ss.str();
    }
};
