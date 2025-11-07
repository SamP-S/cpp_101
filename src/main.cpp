// std lib
#include <iostream>
// internal
#include "i_indexed.hpp"
#include "array.hpp"
#include "list.hpp"
#include "queue.hpp"
#include "stack.hpp"

#define TEST_INDEXED 		false
#define TEST_INDEXED_RANGE 	6

#define TEST_ORDERED		true
#define TEST_ORDERED_PUSHES 12
#define TEST_ORDERED_POPS	5

void testIndexed(std::string _name, IIndexed<int>* _indexed) {
    std::cout << "START TEST: " << _name << std::endl;
    std::cout << _name << " = " << _indexed->toString() << std::endl;
    _indexed->fill(1);
    std::cout << _name << " = " << _indexed->toString() << std::endl;
    _indexed->clear();
    std::cout << _name << " = " << _indexed->toString() << std::endl;
    for (int i = 0; i < TEST_INDEXED_RANGE; i++) {
		(*_indexed)[i] = i;
		std::cout << _name << " = " << _indexed->toString() << std::endl;
	}
   	std::cout << "END TEST: " << _name << std::endl << std::endl;
}

void testOrdered(std::string _name, IOrdered<int>* _ordered) {
	std::cout << "START TEST: " << _name << std::endl;
	std::cout << _name << " = " << _ordered->toString() << std::endl;
	for (int i = 0; i < TEST_ORDERED_PUSHES; i++) {
		_ordered->push(i);
		std::cout << _name << " = " << _ordered->toString() << std::endl;
	}
	for (int i = 0; i < TEST_ORDERED_POPS; i++) {
		_ordered->pop();
		std::cout << _name << " = " << _ordered->toString() << std::endl;
	}
	std::cout << "END TEST: " << _name << std::endl << std::endl;
}

int main() {
	if (TEST_INDEXED) {
		// fixed sized array
		Array<int, 8>* array = new Array<int, 8>();
		testIndexed("array", array);
		// dynamically sized array
		List<int>* list = new List<int>(3);
		testIndexed("list", list);
	}	

	if (TEST_ORDERED) {
		// fifo queue
		Queue<int>* queue = new Queue<int>(4);
		testOrdered("queue", queue);
		// filo stack
		Stack<int>* stack = new Stack<int>(4);
		testOrdered("stack", stack);
	}
}
