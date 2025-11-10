#pragma once

// std lib
#include <exception>
#include <cstring>
#include <sstream>

/*
    Data Structure: Statically Sized Array
*/

template<typename T, size_t SIZE>
class Array {
private: 
    T m_data[SIZE] = {};

public:
    // constructor
    Array() = default;

    // destructor
    ~Array() = default;

    // get fixed size of array
    size_t size() {
        return SIZE;
    }

    // fill all elements with value
    void fill(T _value) {
        for (size_t i = 0; i < SIZE; i++) {
            m_data[i] = _value;
        }
    }
    
    // set all values to default "0"
    void clear() {
        this->fill(T());
    }
    
    // overload index operator
    T& operator[](size_t _index) {
        if (_index >= SIZE) {
            throw std::out_of_range("Array: [] out of range");
        }
        return m_data[_index];
    }

    // convert array to string
    std::string toString() {
        std::stringstream ss;
        ss << "{ size=" << SIZE << "; "; 
		ss << m_data[0];
        for (size_t i = 1; i < SIZE; i++) {
            ss << ", " << m_data[i];
        }
        ss << " }";
        return ss.str();
    }
};
