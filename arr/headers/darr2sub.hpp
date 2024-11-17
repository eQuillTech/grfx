//double sub arrays (m x n) - P. Ahrenkiel

#ifndef _DARR2SUB_
#define _DARR2SUB_

#include <iostream>

#ifndef _ARR2SUB_
#include "arr2sub.hpp"
#endif

namespace arr {
    class darr2;

    typedef arr2sub<double> double_arr2sub;

//
    class darr2sub : public double_arr2sub {
    private:

    public:
        darr2sub(darr2 *A, const std::size_t iRow, const std::size_t iCol, const std::size_t nRows,
                 const std::size_t nCols) : double_arr2sub(A, iRow, iCol, nRows, nCols) {}

        darr2sub(const double_arr2sub &A) : double_arr2sub(A.data(), A.index(0), A.index(1), A.size(0), A.size(1)) {}

        darr2 operator+() const;

        darr2 operator-() const;

        darr2 operator+(const darr2sub &A) const;

        darr2 operator-(const darr2sub &A) const;

        void operator=(const darr2 &A);

        void operator+=(const darr2 &A);

        void operator-=(const darr2 &A);

        darr2 operator/(const double x) const;

        void operator*=(const double x);

        void operator/=(const double x);

        void operator=(const double &x);

        darr2 pwr(const double x) const;

        darr2 sqr();

        darr2 sqrt();
    };

    darr2 pwr(const darr2sub &A, const double x);

    darr2 sqr(const darr2sub &A);

    darr2 sqrt(const darr2sub &A);
}

#endif
