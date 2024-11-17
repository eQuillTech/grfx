//unsigned int arrays (n) - P. Ahrenkiel

#ifndef _UIARR1_
#define _UIARR1_

#include <iostream>

#ifndef _ARR1_
#include "arr1.hpp"
#endif

namespace arr {
    typedef unsigned int uint;

    typedef arr1<uint> uint_arr1;

//
    class uiarr1 : public uint_arr1 {
    private:

    public:
        uiarr1(const std::size_t n = 0, const uint *a = NULL) : uint_arr1(n, a) {}

        uiarr1(const uint_arr1 &A);

        uiarr1(const darr1 &A);

        uiarr1 operator=(const uint &x) { return uint_arr1::operator=(x); }
    };
}

#endif
