#pragma once

// std lib
#include <cstring>
#include <functional>
// internal
#include "common/i_data_structure.hpp"

template<typename K, typename V>
class IBTreeKV : public IDataStructure {
public:
	// constructor/destructor
	IBTreeKV() = default;
	virtual ~IBTreeKV() = default;

	// core
	virtual void insert(K _key, V _value) = 0;
	virtual	bool remove(K _key) = 0;
	virtual bool contains(K _key) = 0;
	virtual V* get(K _key) = 0;
	virtual size_t height() = 0;

	// traversal
	virtual void inOrder(std::function<void(K& _key, V& _value)> _fn) = 0;		// sorted output (BST)
	virtual void preOrder(std::function<void(K& _key, V& _value)> _fn) = 0;		// copying trees
	virtual void postOrder(std::function<void(K& _key, V& _value)> _fn) = 0;	// deleting trees
	virtual void levelOrder(std::function<void(K& _key, V& _value)> _fn) = 0;	// breadth first search (BFS)

	// IDataStructure overrides
	virtual size_t size() override = 0;
	virtual size_t allocated() override = 0;
	virtual bool empty() override = 0;
	virtual void clear() override = 0;
	virtual std::string toString() override = 0;
};
