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
	Data Structure: Doubly Linked List
*/

template<typename T>
class DoublyLinkedList : public ISequence<T> {
private: 
	
	struct DoublyLinkedNode {
		T data;
		DoublyLinkedNode* pNext;
		DoublyLinkedNode* pPrev;
	};

	DoublyLinkedNode* m_pFirst;
	size_t m_size;

public:
	// O(1): constructor
	DoublyLinkedList() {
		m_pFirst = nullptr;
		m_size = 0;
	} 
	
	// O(n): destructor
	~DoublyLinkedList() {
		this->clear();
	}

	// O(1): get used size of dynamic array
	size_t size() override {
		return m_size;
	}

	// O(1): get allocated memory size of dynamic array
	size_t allocated() override {
		return m_size * sizeof(DoublyLinkedNode) + sizeof(DoublyLinkedList);
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
		DoublyLinkedNode* pNode = m_pFirst;
		while (pNode != nullptr) {
			pNode->data = _value;
			pNode = pNode->pNext;
		}
	}
	
	// O(n): overload index operator
	T& operator[](size_t _index) override {
		if (_index >= m_size) {
			throw std::out_of_range("Cannot access element out of range");
		}
		size_t i = 0;
		DoublyLinkedNode* pNode = m_pFirst;
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
		DoublyLinkedNode* pFront = new DoublyLinkedNode();
		pFront->data = _elem;
		pFront->pNext = m_pFirst;
		pFront->pPrev = nullptr;
		if (m_pFirst != nullptr) {
			m_pFirst->pPrev = pFront;
		}
		m_pFirst = pFront;
		m_size++;
	}

	// O(1): pop front
	T pop_front() override {
		if (this->empty()) {
			throw std::out_of_range("Cannot pop from empty list");
		}
		DoublyLinkedNode* pTmp = m_pFirst;
		T ret = m_pFirst->data;
		m_pFirst = m_pFirst->pNext;
		if (m_pFirst != nullptr) {
			m_pFirst->pPrev = nullptr;
		}
		m_size--;
		delete pTmp;
		return ret;
	}

	// O(n): push back
	void push_back(T _elem) override {
		if (this->empty()) {
			this->push_front(_elem);
			return;
		}
		DoublyLinkedNode* pNode = m_pFirst;
		while (pNode->pNext != nullptr) {
			pNode = pNode->pNext;
		}
		DoublyLinkedNode* pNew = new DoublyLinkedNode();
		pNew->data = _elem;
		pNew->pNext = nullptr;
		pNew->pPrev = pNode;
		pNode->pNext = pNew;
		m_size++;
	}

	// O(n): pop back
	T pop_back() override {
		if (this->empty()) {
			throw std::out_of_range("Cannot pop from empty list");
		}
		if (m_pFirst->pNext == nullptr) {
			return this->pop_front();
		}
		DoublyLinkedNode* pNode = m_pFirst;
		while (pNode->pNext != nullptr) {
			pNode = pNode->pNext;
		}
		T ret = pNode->data;
		pNode->pPrev->pNext = nullptr;
		delete pNode;
		m_size--;
		return ret;
	}

	// O(n): insert element at index
	void insert(size_t _index, T _elem) override {
		if (_index >= m_size) {
			this->push_back(_elem);
			return;
		}
		if (_index == 0) {
			this->push_front(_elem);
			return;
		}
		DoublyLinkedNode* pNode = m_pFirst;
		for (size_t i = 0; i < _index; i++) {
			pNode = pNode->pNext;
		}
		DoublyLinkedNode* pNew = new DoublyLinkedNode();
		pNew->data = _elem;
		pNew->pNext = pNode;
		pNew->pPrev = pNode->pPrev;
		pNode->pPrev->pNext = pNew;
		pNode->pPrev = pNew;
		m_size++;
	}

	// O(n): remove element at index
	T remove(size_t _index) override {
		if (_index >= m_size) {
			return this->pop_back();
		}
		if (_index == 0) {
			return this->pop_front();
		}
		DoublyLinkedNode* pNode = m_pFirst;
		for (size_t i = 0; i < _index; i++) {
			pNode = pNode->pNext;
		}
		T ret = pNode->data;
		pNode->pPrev->pNext = pNode->pNext;
		if (pNode->pNext != nullptr) {
			pNode->pNext->pPrev = pNode->pPrev;
		}
		delete pNode;
		m_size--;
		return ret;
	}

	// O(n): convert array to string
	std::string toString() override {
		std::stringstream ss;
		ss << "{ size=" << m_size << "; alloc=" << this->allocated() << "; ";
		DoublyLinkedNode* pNode = m_pFirst;
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
