// std lib
#include <iostream>
// internal
#include "i_indexed.hpp"
#include "array.hpp"
#include "queue.hpp"
#include "stack.hpp"


void testIndexed(std::string _name, IIndexed<int>* _indexed) {
    std::cout << "START TEST: " << _name << std::endl;
    std::cout << _name << " = " << _indexed->toString() << std::endl;
    _indexed->fill(1);
    std::cout << _name << " = " << _indexed->toString() << std::endl;
    _indexed->clear();
    std::cout << _name << " = " << _indexed->toString() << std::endl;
    for (int i = 0; i < 6; i++) {
		(*_indexed)[i] = i;
		std::cout << _name << " = " << _indexed->toString() << std::endl;
	}
   	std::cout << "END TEST: " << _name << std::endl << std::endl;
}

void testQueue() {
    std::cout << "START TEST: QUEUE" << std::endl;
    Queue<int> queue(5);
    std::cout << "queue = " << queue.toString() << std::endl;
    for (int i = 0; i < 12; i++) {
        queue.push(i);
        std::cout << "queue = " << queue.toString() << std::endl;
    }
    for (int i = 0; i < 5; i++) {
        queue.pop();
        std::cout << "queue = " << queue.toString() << std::endl;
    }
    std::cout << "END TEST: QUEUE" << std::endl << std::endl;
}

void testStack() {
    std::cout << "START TEST: STACK" << std::endl;
    Stack<int> stack(5);
    std::cout << "stack = " << stack.toString() << std::endl;
    for (int i = 0; i < 12; i++) {
        stack.push(i);
        std::cout << "stack = " << stack.toString() << std::endl;
    }
    for (int i = 0; i < 5; i++) {
        stack.pop();
        std::cout << "stack = " << stack.toString() << std::endl;
    }
    std::cout << "END TEST: STACK" << std::endl << std::endl;
}

int main() {
	Array<int, 8>* array = new Array<int, 8>();
    testIndexed("array", array);
    testQueue();
    testStack();
}
