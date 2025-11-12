#pragma once

// std lib
#include <random>
// internal
#include "common/global.hpp"

template<typename T>
size_t partition(T* _pArr, size_t _low, size_t _high) {
	// choose random pivot location, swap to back
	size_t range = _high - _low + 1;
	size_t pivot = _low + rand() % range;
	T pivot_val = _pArr[pivot];
	swap(_pArr, pivot, _high);
	// set low cursor
	int low_cursor = _low;
	int high_cursor = _high - 1;
	while (low_cursor <= high_cursor) {
		if (_pArr[low_cursor] <= pivot_val) {
			low_cursor++;
		} else if (_pArr[high_cursor] >= pivot_val) {
			high_cursor--;
		} else {
			swap(_pArr, low_cursor, high_cursor);
			low_cursor++;
			high_cursor--;
		}
	}
	// unswap pivot from back
	swap(_pArr, _high, low_cursor);
	return low_cursor;
}

template<typename T>
void quick_sort_impl(T* _pArr, size_t _low, size_t _high) {
	// only applies if range > 1
	if (_low < _high) {
		size_t pivot = partition(_pArr, _low, _high);
		quick_sort_impl(_pArr, _low, pivot-1);
		quick_sort_impl(_pArr, pivot+1, _high);  
	}
}

// O(n log(n)): quick sort using random pivot
template<typename T>
void quick_sort(T* _pArr, size_t _size) {
	// return if naturally sorted
	if (_size <= 1) {
		return;
	} else if (_size == 2) {
		// swap pair if necessary
		if (_pArr[0] > _pArr[1]) {
			swap(_pArr, 0, 1);
		}
		return;
	}
	// apply quick sort w/ sub arrays
	quick_sort_impl(_pArr, 0, _size-1);
}
