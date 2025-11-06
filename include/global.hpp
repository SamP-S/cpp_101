#pragma once

#include <exception>
#include <cstring>
#include <sstream>

// resize memory at pointer keeping existing data in place
template<typename T>
void memresize(T** _p, size_t _size, size_t _newSize) {
    T* pNew = (T*)malloc(_newSize * sizeof(T));
    std::memcpy((void*)pNew, (void*)*_p, _size * sizeof(T));
    T* pTmp = *_p;
    *_p = pNew;
    free(pTmp);
}

