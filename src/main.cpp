// std lib
#include <iostream>
// internal
#include "i_data_structure.hpp"
#include "array.hpp"
#include "list.hpp"
// #include "queue.hpp"
// #include "stack.hpp"

#define TEST_ARRAY 			false
#define TEST_ARRAY_SIZE 	16
#define TEST_ARRAY_RANGE 	12

#define TEST_LIST	true
#define TEST_INIT	3
#define TEST_PUSHES 6
#define TEST_POPS	4

void testArray(std::string _name, Array<int, TEST_ARRAY_SIZE>* _array) {
	std::cout << "START TEST: " << _name << std::endl;
    std::cout << _name << " = " << _array->toString() << std::endl;
    _array->fill(1);
    std::cout << _name << " = " << _array->toString() << std::endl;
    _array->clear();
    std::cout << _name << " = " << _array->toString() << std::endl;
    for (int i = 0; i < TEST_ARRAY_RANGE; i++) {
		(*_array)[i] = TEST_ARRAY_RANGE - i - 1;
		std::cout << _name << " = " << _array->toString() << std::endl;
	}
   	std::cout << "END TEST: " << _name << std::endl << std::endl;
}

void printDS(std::string _name, IDataStructure<int>* _ds) {
	std::cout << _name << " = " << _ds->toString() << std::endl;
}

void testDS(std::string _name, IDataStructure<int>* _ds) {
    std::cout << "START TEST: " << _name << std::endl;
    printDS(_name, _ds);
    _ds->fill(1);
    printDS(_name, _ds);
    _ds->clear();
    printDS(_name, _ds);
    for (int i = 0; i < TEST_PUSHES; i++) {
		_ds->push(TEST_PUSHES - i - 1);
		printDS(_name, _ds);
	}
	for (int i = 0; i < TEST_POPS; i++) {
		_ds->pop();
		printDS(_name, _ds);
	}
	_ds->push_front(99);
	printDS(_name, _ds);
	_ds->pop_front();
	printDS(_name, _ds);
	_ds->insert(3, 12);
	printDS(_name, _ds);
	_ds->remove(3);
	printDS(_name, _ds);
	
   	std::cout << "END TEST: " << _name << std::endl << std::endl;
}

int main() {
	// fixed sized array
	if (TEST_ARRAY) {
		Array<int, 16>* array = new Array<int, 16>();
		testArray("array", array);
	}

	// dynamically sized array
	if (TEST_LIST) {
		List<int>* list = new List<int>(TEST_INIT);
		testDS("list", list);
	}	

	// if (TEST_ORDERED) {
	// 	// fifo queue
	// 	Queue<int>* queue = new Queue<int>(4);
	// 	testDS("queue", queue);
	// 	// filo stack
	// 	Stack<int>* stack = new Stack<int>(4);
	// 	testDS("stack", stack);
	// }
}
