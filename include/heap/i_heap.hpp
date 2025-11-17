#pragma once

// std lib
#include <cstring>
#include <functional>
// internal
#include "common/i_data_structure.hpp"

template<typename T, typename Compare = std::less<T>>
class IHeap : public IDataStructure {
private:

public:
	// constructor/destructor
	IHeap() = default;
	~IHeap() = default;

	// core
	virtual void push(T _value) = 0;
	virtual T pop() = 0;
	virtual T& top() = 0;

	// traversal
	virtual void levelOrder(std::function<void(K& _key, V& _value)> _fn) = 0;	// breadth first search (BFS)

	// IDataStructure overrides
	virtual size_t size() override = 0;
	virtual size_t allocated() override = 0;
	virtual bool empty() override = 0;
	virtual void clear() override = 0;
	virtual std::string toString() override = 0;

};
