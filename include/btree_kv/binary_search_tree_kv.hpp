#pragma once

// std lib
#include <cstring>
#include <functional>
// internal
#include "btree_kv/i_btree_kv.hpp"
#include "abstract/queue.hpp"
#include "sequence/circular_doubly_linked_list.hpp"

template<typename K, typename V>
class BinarySearchTreeKV : public IBTreeKV<K, V> {
private:
	struct BNodeKV {
		K key = K();
		V value = V();
		BNodeKV* left = nullptr;
		BNodeKV* right = nullptr;

		BNodeKV() = default;
		BNodeKV(K _key, V _value)
			: key(_key), value(_value) {}
	};

	BNodeKV* m_pRoot;
	size_t m_size;
	size_t m_height;

	// find node of key, or correct new location
	BNodeKV** findRecursive(BNodeKV** _ppNode, K _key, size_t& _height) {
		assert(_ppNode != nullptr && "Cannot find in null pointer pointer tree");
		// if current pointer to node is null, then found
		if (*_ppNode == nullptr) {
			return _ppNode;
		}
		// if current node at pointer matches key, then found
		if ((*_ppNode)->key == _key) {
			return _ppNode;
		}
		// otherwise branch to relevant leaf
		++_height;
		if (_key < (*_ppNode)->key) {
			return findRecursive(&((*_ppNode)->left), _key, _height);
		} else {
			return findRecursive(&((*_ppNode)->right), _key, _height);
		}
	}

	// post order delete children then delete node
	void deleteRecursive(BNodeKV** _ppNode) {
		assert(_ppNode != nullptr && "Cannot remove in null pointer pointer tree");
		// skip null nodes
		if (*_ppNode == nullptr) {
			return;
		}
		// remove branches
		this->deleteRecursive(&(*_ppNode)->left);
		this->deleteRecursive(&(*_ppNode)->right);
		// remove self
		delete *_ppNode;
		*_ppNode = nullptr;
	}

	// traverse in sorted order, l -> n -> r
	void inOrderRecursive(BNodeKV** _ppNode, std::function<void(K& _key, V& _value)> _fn) {
		assert(_ppNode != nullptr && "Cannot traverse null tree");
		// skip null nodes
		if (*_ppNode == nullptr) {
			return;
		}
		// apply fn
		inOrderRecursive(&(*_ppNode)->left, _fn);
		_fn((*_ppNode)->key, (*_ppNode)->value);
		inOrderRecursive(&(*_ppNode)->right, _fn);
	}

	// travese in copying order, n -> l -> r
	void preOrderRecursive(BNodeKV** _ppNode, std::function<void(K& _key, V& _value)> _fn) {
		assert(_ppNode != nullptr && "Cannot traverse null tree");
		// apply fn
		_fn((*_ppNode)->key, (*_ppNode)->value);
		inOrderRecursive(&(*_ppNode)->left, _fn);
		inOrderRecursive(&(*_ppNode)->right, _fn);
	}

	// traverse in deleting order, l -> r -> n
	void postOrderRecursive(BNodeKV** _ppNode, std::function<void(K& _key, V& _value)> _fn) {
		assert(_ppNode != nullptr && "Cannot traverse null tree");
		// apply fn
		inOrderRecursive(&(*_ppNode)->left, _fn);
		inOrderRecursive(&(*_ppNode)->right, _fn);
		_fn((*_ppNode)->key, (*_ppNode)->value);
	}

	// recursively explore tree and calc size
	size_t getHeightRecursive(BNodeKV* _pNode) {
		if (_pNode == nullptr) {
			return 0;
		}	
		return 1 + std::max(
			getHeightRecursive(_pNode->left),
			getHeightRecursive(_pNode->right)
		);
	}

public:
	// constructor
	BinarySearchTreeKV()
		: m_pRoot(nullptr), m_size(0), m_height(0) {}

	// destructor
	~BinarySearchTreeKV() {
		this->clear();
	}

	// insert node at key
	void insert(K _key, V _value) override {
		// find matching position for key
		size_t height = 1;
		BNodeKV** ppNode = this->findRecursive(&m_pRoot, _key, height);
		// found existing node matching key, reassign value
		if ((*ppNode) != nullptr) {
			(*ppNode)->value = _value;
			return;
		// found position for new node for key, insert
		} else {	
			(*ppNode) = new BNodeKV(_key, _value);
			m_size++;
			if (height > m_height) {
				m_height++;
			}
		}
	}

	// remove node with key and its children
	bool remove(K _key) override {
		// find matching position for key
		size_t height = 1;
		BNodeKV** ppNode = this->findRecursive(&m_pRoot, _key, height);
		// found existing node matching key, delete recursively
		if ((*ppNode) != nullptr) {
			this->deleteRecursive(ppNode);
			m_height = getHeightRecursive(m_pRoot);
			return true;
		// found position for new node for key, pass
		} else {
			return false;
		}
	}

	// check a node exists with key
	bool contains(K _key) override {
		// find matching position for key
		size_t height = 1;
		BNodeKV** ppNode = this->findRecursive(&m_pRoot, _key, height);
		return (*ppNode) != nullptr;
	}

	// get value at node of key
	V* get(K _key) override {
		// find matching position for key
		size_t height = 1;
		BNodeKV** ppNode = this->findRecursive(&m_pRoot, _key, height);
		// found existing node matching key, return pointer to value
		if ((*ppNode) != nullptr) {
			return &(*ppNode)->value;
		// found position for new node for key, return null
		} else {
			return nullptr;
		}
	}	

	// get tree height
	size_t height() override {
		return m_height;
	}

	// traverse in sorted order, l -> n -> r
	void inOrder(std::function<void(K& _key, V& _value)> _fn) override {
		this->inOrderRecursive(&m_pRoot, _fn);
	}

	// travese in copying order, n -> l -> r
	void preOrder(std::function<void(K& _key, V& _value)> _fn) override {
		this->preOrderRecursive(&m_pRoot, _fn);
	}

	// traverse in deleting order, l -> r -> n
	void postOrder(std::function<void(K& _key, V& _value)> _fn) override {
		this->postOrderRecursive(&m_pRoot, _fn);
	}

	// traverse in bfs order h0 -> h1 -> h2 ...
	void levelOrder(std::function<void(K& _key, V& _value)> _fn) override {
		// skip if tree empty
		if (m_pRoot == nullptr) {
			return;
		}
		// implement using queue
		Queue<BNodeKV*> q = Queue<BNodeKV*>(new CircularDoublyLinkedList<BNodeKV*>());
		q.enqueue(m_pRoot);

		while(!q.empty()) {
			// pop front node
			BNodeKV* pNode = q.dequeue();
			// skip if null node
			if (pNode == nullptr) {
				continue;
			}
			// otherwise apply fn
			_fn(pNode->key, pNode->value);
			// enqueue children
			q.enqueue(pNode->left);
			q.enqueue(pNode->right);
		}
	}

	// get node count
	size_t size() override {
		return m_size;
	}

	// get allocated memory size
	size_t allocated() override {
		return m_size * sizeof(BNodeKV) + sizeof(*this);
	}

	// bool test if node count is 0
	bool empty() override {
		return m_size == 0;
	}

	// remove all nodes, return to empty state
	void clear() override {
		this->deleteRecursive(&m_pRoot);
		m_height = 0;
		m_size = 0;
	}

	// convert to string
	std::string toString() override {
		std::stringstream ss;
		ss << "{ size=" << m_size << "; allocated=" << this->allocated() << "; height=" << m_height << "; ";
		// traverse in order
		this->inOrder([&ss](K& key, V& value) {
			ss << key << ": " << value << ", ";
		});
		std::string result = ss.str();
		// replace final ", "
		if (m_size > 0) {
			result.pop_back();
			result.pop_back();
		}
		result += "}";
		return result;
	}
};
