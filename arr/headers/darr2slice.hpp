//array slices (n) - P. Ahrenkiel

#ifndef _DARR2SLICE_
#define _DARR2SLICE_

#include <iostream>

#ifndef _ARR2SLICE_
#include "arr2slice.hpp"
#endif

namespace arr {
    class darr2;

    typedef arr2slice<double> double_arr2slice;

//
    class darr2slice : public double_arr2slice {
    private:

    public:
        darr2slice(darr2 *A, const std::size_t iDim, const std::size_t iIndex) : double_arr2slice(A, iDim, iIndex) {}

        darr2slice(const double_arr2slice &A) : double_arr2slice(A.data(), A.dim(), A.index()) {}

        darr2 operator+() const;

        darr2 operator-() const;

        darr2 operator+(const darr2slice &A) const;

        darr2 operator-(const darr2slice &A) const;

        void operator=(const darr2 &A);

        void operator+=(const darr2 &A);

        void operator-=(const darr2 &A);

        darr2 operator/(const double x) const;

        void operator*=(const double x);

        void operator/=(const double x);

        void operator=(const double x);

        darr1 pwr(const double x) const;

        darr1 sqr() const;

        darr1 sqrt() const;

        double mag();

        double magsqr();

        friend darr2 operator*(double x, const darr2slice &A);

        friend std::ostream &operator<<(std::ostream &os, const darr2slice &A) { return os << darr2(A); }
    };

    darr1 pwr(const darr2slice &A, const double x);

    darr1 sqr(const darr2slice &A);

    darr1 sqrt(const darr2slice &A);

    double mag(const darr2slice &A);

    double magsqr(const darr2slice &A);
}

#endif
