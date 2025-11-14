// std lib
#include <iostream>
#include <random>
#include <sstream>
// internal
#include "common/global.hpp"
#include "common/i_data_structure.hpp"
#include "array.hpp"
#include "sequence/i_sequence.hpp"
#include "sequence/dynamic_array.hpp"
#include "sequence/circular_dynamic_array.hpp"
#include "sequence/linked_list.hpp"
#include "sequence/circular_linked_list.hpp"
#include "sequence/doubly_linked_list.hpp"
#include "sequence/circular_doubly_linked_list.hpp"
#include "sorting/merge_sort.hpp"
#include "sorting/bubble_sort.hpp"
#include "sorting/quick_sort.hpp"
#include "btree_kv/i_btree_kv.hpp"
#include "btree_kv/binary_search_tree_kv.hpp"

#define TEST_ARRAY 			false
#define TEST_ARRAY_SIZE 	16
#define TEST_ARRAY_RANGE 	12

#define TEST_SEQUENCE		false
#define TEST_PUSHES 		7
#define TEST_POPS			3

#define TEST_SORT			false
#define TEST_SORT_SIZE		12
#define TEST_SORT_MAX		(1 << 8)

#define TEST_BTREEKV		true
#define TEST_BTREEKV_SIZE	7
#define TEST_BTREEKV_MAX	(1 << 8)

template<typename T>
std::string arrayToString(T* _pArr, size_t _size) {
	std::stringstream ss;
	ss << "{ size=" << _size << "; ";
	if (_size != 0) {
		ss << _pArr[0];
	}
	for (size_t i = 1; i < _size; i++) {
		ss << ", " << _pArr[i];
	}
	ss << " }";
	return ss.str();
}

template<typename T>
void printArray(std::string _name, T* _pArr, size_t _size) {
	std::cout << _name << " = " << arrayToString<T>(_pArr, _size) << std::endl;
}

template<typename T>
T* genRandArray(size_t _size) {
	T* pArr = memalloc<T>(_size);
	for (size_t i = 0; i < _size; i++) {
		pArr[i] = (int)(rand() % TEST_SORT_MAX);
	}
	return pArr;
}

template<typename T>
T* genRevArray(size_t _size) {
	T* pArr = memalloc<T>(_size);
	for (size_t i = 0; i < _size; i++) {
		pArr[i] = _size - i - 1;
	}
	return pArr;
}

void printDS(std::string _name, IDataStructure* _ds) {
	std::cout << _name << " = " << _ds->toString() << std::endl;
}

void printSeq(std::string _name, ISequence<int>* _seq) {
	std::cout << _name << " = " << _seq->toString() << std::endl;
}

void testArray(std::string _name, Array<int, TEST_ARRAY_SIZE>* _array) {
	std::cout << "START TEST: " << _name << std::endl;
    std::cout << _name << " = " << _array->toString() << std::endl;
    _array->fill(1);
    std::cout << _name << " = " << _array->toString() << std::endl;
    _array->clear();
    std::cout << _name << " = " << _array->toString() << std::endl;
    for (int i = 0; i < TEST_ARRAY_RANGE; i++) {
		(*_array)[i] = TEST_ARRAY_RANGE - i - 1;
	}
	std::cout << _name << " = " << _array->toString() << std::endl;
   	std::cout << "END TEST: " << _name << std::endl << std::endl;
}

void testSequence(std::string _name, ISequence<int>* _seq) {
    std::cout << "START TEST: " << _name << std::endl;
    printSeq("init", _seq);
    for (int i = 0; i < TEST_PUSHES; i++) {
		_seq->push_back(TEST_PUSHES - i - 1);
	}
	printSeq("push-back\t", _seq);
	for (int i = 0; i < TEST_POPS; i++) {
		_seq->pop_back();
	}
	printSeq("pop-back\t", _seq);
	_seq->push_front(99);
	printSeq("push-front\t", _seq);
	_seq->pop_front();
	printSeq("pop-front\t", _seq);
	_seq->insert(2, 999);
	printSeq("insert\t\t", _seq);
	_seq->remove(2);
	printSeq("remove\t\t", _seq);
	_seq->insert(_seq->size() + 4, 9999);
	printSeq("insert-end\t", _seq);
	_seq->remove(_seq->size());
	printSeq("remove-end\t", _seq);
	_seq->fill(1);
    printSeq("fill\t\t", _seq);
    _seq->clear();
    printSeq("clear\t\t", _seq);
	
   	std::cout << "END TEST: " << _name << std::endl << std::endl;
}

void testSorting(std::string _name, void(*_fn)(int*, size_t)) {
	size_t size = TEST_SORT_SIZE;
	int* pArr = nullptr;
	std::cout << "START TEST: " << _name << std::endl;
	
	// sort random array
	pArr = genRandArray<int>(size);
	printArray<int>("rand-before\t", pArr, size);
	_fn(pArr, size);
	printArray<int>("rand-after\t", pArr, size);
	memfree<int>(pArr);
	
	// sort reverse order array
	pArr = genRevArray<int>(size);
	printArray<int>("rev-before\t", pArr, size);
	_fn(pArr, size);
	printArray<int>("rev-after\t", pArr, size);
	memfree<int>(pArr);

	std::cout << "END TEST: " << _name << std::endl;
}

void testBTreeKV(std::string _name, IBTreeKV<int, int>* _btree) {
	std::cout << "START TEST: " << _name << std::endl;
	printDS("initial\t\t", (IDataStructure*)_btree);
	size_t size = TEST_BTREEKV_SIZE;
	int find = size / 2;
	for (size_t i = 0; i < size; i++) {
		int k = rand() % TEST_BTREEKV_MAX;
		_btree->insert(k, i);
		if (i == find) {
			find = k;
		}
		printDS("insert\t\t", (IDataStructure*)_btree);
	}
	_btree->remove(find);
	printDS("remove-key\t", (IDataStructure*)_btree);
	_btree->clear();
	printDS("clear\t\t", (IDataStructure*)_btree);
	std::cout << "END TEST: " << _name << std::endl;
}

int main() {
	// fixed sized array
	if (TEST_ARRAY) {
		Array<int, 16>* array = new Array<int, 16>();
		testArray("array", array);
	}

	// dynamically sized array
	if (TEST_SEQUENCE) {
		std::pair<std::string, ISequence<int>*> seqs[] = {
			{"dynamic-array", new DynamicArray<int>()},
			{"circular-dynamic-array", new CircularDynamicArray<int>()},
			{"linked-list", new LinkedList<int>()},
			{"circular-linked-list", new CircularLinkedList<int>()},
			{"doubly-linked-list", new DoublyLinkedList<int>()},
			{"circular-doubly-linked-list", new CircularDoublyLinkedList<int>()}
		};

		for (const auto& seq : seqs) {
			testSequence(seq.first, seq.second);
			delete seq.second;
		}
	}	

	// sorting algorithms
	if (TEST_SORT) {
		std::pair<std::string, void(*)(int*, size_t)> sorts[] = {
			{"merge-sort", merge_sort<int>},
			{"bubble-sort", bubble_sort<int>},
			{"bubble-sort-fast", bubble_sort_fast<int>},
			{"quick-sort", quick_sort<int>}
		};

		for (const auto& sort : sorts) {
			testSorting(sort.first, sort.second);
		}
	}

	if (TEST_BTREEKV) {
		std::pair<std::string, IBTreeKV<int, int>*> btrees[] = {
			{"binary-search-tree-kv", new BinarySearchTreeKV<int, int>()}
		};

		for (const auto& btree : btrees) {
			testBTreeKV(btree.first, btree.second);
			delete btree.second;
		}
	}
}
