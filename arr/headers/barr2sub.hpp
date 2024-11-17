//bool sub arrays (m x n) - P. Ahrenkiel

#ifndef _BARR2SUB_
#define _BARR2SUB_

#include <iostream>

#ifndef _ARR2SUB_
#include "arr2sub.hpp"
#endif

namespace arr {
    class barr2;

    typedef arr2sub<bool> bool_arr2sub;

//
    class barr2sub : public bool_arr2sub {
    private:

    public:
        barr2sub(barr2 *A, const std::size_t iRow, const std::size_t iCol, const std::size_t nRows,
                 const std::size_t nCols) : bool_arr2sub(A, iRow, iCol, nRows, nCols) {}

        barr2sub(const bool_arr2sub &A) : bool_arr2sub(A.data(), A.index(0), A.index(1), A.size(0), A.size(1)) {}

        barr2 operator|(const barr2sub &A) const;

        barr2 operator&(const barr2sub &A) const;

        void operator=(const barr2 &A);

        void operator|=(const barr2 &A);

        void operator&=(const barr2 &A);

        void operator=(const bool &x);

        bool hasTrue() const;

        bool hasFalse() const;
    };
}

#endif
