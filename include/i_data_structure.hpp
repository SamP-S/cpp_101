#pragma once

// std lib
#include <exception>
#include <cstring>
#include <sstream>

/*
    Interface: Data Structures
*/

template<typename T>
class IDataStructure {
public:
    // constructor
    IDataStructure() = default;

    // destructor
    ~IDataStructure() = default;

    // get used size of data structure
    virtual size_t size() = 0;

	// get allocated size of data structure
	virtual size_t allocated() = 0;

	// bool check if empty
	virtual bool empty() = 0;

	// resize allocated size of data structure
	virtual void resize(size_t _n) = 0;

    // fill all used elements with value
    virtual void fill(T _value) = 0;
    
    // set all used values to default "0"
    virtual void clear() = 0;
	
	// access existing element
	virtual T& operator[](size_t _index) = 0;

	// add element to end of list
	virtual void push(T _elem) = 0;

	// remove element from end of list and return a copy
	virtual T pop() = 0;

	// add element to front of list
	virtual void push_front(T _elem) = 0;

	// remove element from front of list and return a copy
	virtual T pop_front() = 0;

	// insert element at arbritrary index in used range + 1
	virtual void insert(size_t _index, T _elem) = 0;

	// remove used element at arbritrary index
	virtual T remove(size_t _index) = 0;

    // convert used elements to string for debug
    virtual std::string toString() = 0;
};

