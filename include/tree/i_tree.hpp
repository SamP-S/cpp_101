#pragma once

// std lib
#include <cstring>
// internal
#include "common/global.hpp"
#include "common/i_data_structure.hpp"

enum TraversalOrder {
	PRE_ORDER,
	IN_ORDER,
	POST_ORDER,
	LEVEL_ORDER
};

template<typename T>
struct BNode {
	BNode* left;
	BNode* right;

	bool isLeaf() {
		return (left == nullptr) && (right == nullptr);
	}
};

template<typename T>
class ITree : public IDataStructure<T> {
public:
	// constructor/destructor
	ITree() = default;
	virtual ~ITree() = default;

	// core
	virtual void insert(T _elem) = 0;
	virtual bool remove(T _elem) = 0;
	virtual bool find(T _elem) = 0;
	virtual size_t height() = 0;


	// IDataStructure overrides
	virtual size_t size() override = 0;
	virtual size_t allocated() override = 0;
	virtual bool empty() override = 0;
	virtual void clear() override = 0;
	virtual std::string toString() override = 0;
};
