#pragma once

// std lib
#include <exception>
#include <cstring>
#include <sstream>
//internal
#include "global.hpp"

/*
    Data Structure: Dynamically Sized List
*/

template<typename T>
class List : public IIndexed<T> {
private: 
    T* m_pData;
    size_t m_size;

public:
    // constructor, allow manual init size
    List(size_t _n) {
		_n = nearestBase2(_n);
		m_pData = (T*)malloc(_n * sizeof(T));
		m_size = _n;
	}

    // destructor
    ~List() {
		free(m_pData);
	}

    // get size of list
    size_t size() override {
        return m_size;
    }

    // fill all elements with value
    void fill(T _value) override {
        for (size_t i = 0; i < m_size; i++) {
            m_pData[i] = _value;
        }
    }
    
    // set all values to default "0"
    void clear() override {
        this->fill(T());
    }
    
    // overload index operator
    T& operator[](size_t _index) override {
        if (_index >= m_size) {
			size_t newSize = nearestBase2(_index + 1);
			memresize<T>(&m_pData, m_size, newSize);
   			m_size = newSize;
		}
        return m_pData[_index];
    }

    // convert array to string
    std::string toString() override {
        std::stringstream ss;
      	ss << "{ size=" << m_size << "; "; 
		ss << m_pData[0];
        for (size_t i = 1; i < m_size; i++) {
            ss << ", " << m_pData[i];
        }
        ss << " }";
        return ss.str();
    }
};
