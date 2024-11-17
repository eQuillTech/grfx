//usigned int arrays (m x n) - P. Ahrenkiel

#ifndef _UIARR2_
#define _UIARR2_

#include <iostream>

#ifndef _ARR2_
#include "arr2.hpp"
#endif

namespace arr {
    typedef arr2<std::size_t> uint_arr2;

    class darr2;

//
    class uiarr2 : public uint_arr2 {
    private:

    public:
        uiarr2(const std::size_t N0 = 0, const std::size_t N1 = 0, const std::size_t *ap = NULL) : uint_arr2(N0, N1,
                                                                                                             ap) {}

        uiarr2(const uint_arr2 &A);

        uiarr2 minor(const std::size_t iRow, const std::size_t iCol) const;

        darr2 operator+() const { return +darr2(*this); }

        darr2 operator-() const { return -darr2(*this); }

        darr2 operator+(const darr2 &A) const { return darr2(*this) + A; }

        darr2 operator-(const darr2 &A) const { return darr2(*this) - A; }

        uiarr2 operator=(const std::size_t &x) { return uint_arr2::operator=(x); }

        static uiarr2 zero(const size_t nRows, const size_t nCols);

        static uiarr2 ident(const size_t nRows, const size_t nCols);

        uiarr2 zero() { return *this = uiarr2::zero(size(0), size(1)); }

        uiarr2 ident() { return *this = uiarr2::ident(size(0), size(1)); }
    };
}

#endif
