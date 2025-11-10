#pragma once

// std lib
#include <exception>
#include <cstring>
#include <sstream>
//internal
#include "global.hpp"
#include "i_data_structure.hpp"

/*
    Data Structure: Dynamically Sized List
*/

template<typename T>
class List : public IDataStructure<T> {
private: 
    T* m_pData;
    size_t m_size;
	size_t m_end;

public:
    // O(n): constructor, allow manual init size
    List(size_t _n) {
		size_t allocSize = nearestBase2(_n);
		m_pData = memalloc<T>(allocSize);
		m_size = allocSize;
		m_end = _n;
		this->clear();
	}

    // O(1): destructor
    ~List() {
		memfree<T>(m_pData);
	}

    // O(1): get used size of list
    size_t size() override {
        return m_end;
    }

	// O(1): get allocated memory size of list
	size_t allocated() override {
		return m_size;
	}

	// O(n): resize data structure
	void resize(size_t _n) override {
		size_t newSize = nearestBase2(_n);
		memresize<T>(&m_pData, m_size, newSize);
		m_size = newSize;
	}

    // O(n): fill all elements with value
    void fill(T _value) override {
        for (size_t i = 0; i < m_end; i++) {
            m_pData[i] = _value;
        }
    }
    
    // O(n): set all values to default "0"
    void clear() override {
        this->fill(T());
    }
    
    // O(1): overload index operator
    T& operator[](size_t _index) override {
        if (_index >= m_end) {
			throw std::range_error("Can't index outside of used range");
		}
        return m_pData[_index];
    }

	// O(1)/O(n): push back
	void push(T _elem) override {
		if (m_end >= m_size) {
			this->resize(m_size << 1);
		}
		m_pData[m_end] = _elem;
		m_end++;
	}

	// O(1): pop back
	T pop() override {
		if (m_end == 0) {
			throw std::range_error("Can't pop from list of size 0");
		}
		T ret = m_pData[m_end - 1];
		m_end--;
		return ret;
	}

	// O(n): push front
	void push_front(T _elem) override {
		this->insert(0, _elem);
	}

	// O(n): pop front
	T pop_front() override {
		return this->remove(0);
	}

	// O(n): insert element at index
	void insert(size_t _index, T _elem) override {
		// resize if necessary
		if (m_end >= m_size) {
			this->resize(m_size << 1);
		}
		// push if index at end
		if (_index >= m_end) {
			this->push(_elem);
			return;
		}
		// copy forward and insert
		size_t range = m_end - _index;
		T* pTmp = memalloc<T>(range);
		memcpy<T>(pTmp, m_pData + _index, range);
		memcpy<T>(m_pData + _index + 1, pTmp, range);
		memfree<T>(pTmp);
		m_pData[_index] = _elem;
		m_end++;
	}

	// O(n): remove element at index
	T remove(size_t _index) override {
		// throw error if out of range
		if (_index >= m_size) {
			throw std::range_error("Can't remove an element out of the list range");
		}
		// pop if index at end
		if (_index >= m_end) {
			return this->pop();
		}
		// copy backward and return
		T ret = m_pData[_index];
		size_t range = m_size - _index - 1;
		T* pTmp = memalloc<T>(range);
		memcpy<T>(pTmp, m_pData + _index + 1, range);
		memcpy<T>(m_pData + _index, pTmp, range);
		memfree<T>(pTmp);
		m_pData[m_size - 1] = T();
		m_end--;
		return ret;
	}

    // O(n): convert array to string
    std::string toString() override {
        std::stringstream ss;
      	ss << "{ size=" << m_size << "; used=" << m_end << "; "; 
		ss << m_pData[0];
        for (size_t i = 1; i < m_end; i++) {
            ss << ", " << m_pData[i];
        }
        ss << " }";
        return ss.str();
    }
};
