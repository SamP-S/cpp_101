// std lib
#include <iostream>
// internal
#include "array.hpp"
#include "queue.hpp"


int main() {
    Array<int, 3> arr;
    arr.clear();
    arr.fill(1);
    arr[1] = 2;
    arr[2] = 3;
    std::cout << "array = " << arr.toString() << std::endl;

    Queue<int> q(5);
    std::cout << "queue = " << q.toString() << std::endl;
    for (int i = 0; i < 10; i++) {
        q.push(i);
        std::cout << "queue = " << q.toString() << std::endl;
    }
    for (int i = 0; i < 5; i++) {
        q.pop();
        std::cout << "queue = " << q.toString() << std::endl;
    }
    std::cout << "queue = " << q.toString() << std::endl;

}
