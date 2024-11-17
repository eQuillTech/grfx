// double arrays (n) - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

// #include "cpx.hpp"

#include "arr.hpp"
#include "mth.hpp"
#include "trg.hpp"

namespace arr {

//
darr1 darr1::operator+() const { return *this; }

//
darr1 darr1::operator-() const
{
    darr1 res(*this);
    for (size_t i = 0; i < size(); ++i)
        res(i) *= -1;
    return res;
}

//
darr1 darr1::operator+(const darr1& A) const
{
    darr1 res(*this);
    for (size_t i = 0; i < size(); ++i)
        res(i) += A(i);
    return res;
}

//
darr1 darr1::operator-(const darr1& A) const
{
    darr1 res(*this);
    for (size_t i = 0; i < size(); ++i)
        res(i) -= A(i);
    return res;
}

//
double darr1::dot(const darr1& A) const
{
    double res = 0;
    if (size() != A.size()) {
        err = -1;
        return res;
    }
    for (size_t i = 0; i < size(); ++i)
        res += at(i) * A(i);
    return res;
}

darr1 darr1::operator+=(const darr1& A) { return *this = *this + A; }

darr1 darr1::operator-=(const darr1& A) { return *this = *this - A; }

darr1 darr1::operator/(double x) const { return (1. / x) * (*this); }

darr1 darr1::operator*=(double x) { return *this = x * (*this); }

darr1 darr1::operator/=(double x) { return *this = (*this) / x; }

//
double darr1::sum() const
{
    double res = 0;
    for (size_t i = 0; i < size(); ++i)
        res += at(i);
    return res;
}

//
double darr1::sumSqr() const
{
    double res = 0;
    for (size_t i = 0; i < size(); ++i)
        res += mth::sqr(at(i));
    return res;
}

//
darr1 operator*(double x, const darr1& A)
{
    darr1 res(A);
    for (size_t i = 0; i < A.size(); ++i)
        res(i) = x * A(i);
    return res;
}

//
double darr1::mag() const { return ::sqrt(sumSqr()); }

//
bool darr1::swap(std::size_t i1, std::size_t i2)
{
    if (!((i1 < size() && (i2 < size()))))
        return false;
    double x = (*this)(i1);
    (*this)(i1) = at(i2);
    at(i2) = x;
    return true;
}

//
darr1 darr1::sub(std::size_t iRow, std::size_t nRow) const
{
    if (iRow + nRow > size())
        nRow = size() - iRow;
    darr1 res(nRow);
    for (size_t i = 0; i < nRow; ++i)
        res(i) = at(i + iRow);
    return res;
}

//
darr1 darr1::zero(const size_t n)
{
    darr1 res(n);
    res = 0.;
    return res;
}

//
darr1 darr1::pwr(double x) const
{
    darr1 A(size());
    for (size_t i = 0; i < size(); ++i)
        A(i) = pow(at(i), x);
    return A;
}

darr1 darr1::sqr() const { return pwr(2); }

darr1 darr1::sqrt() const { return pwr(0.5); }

darr1 sqr(const darr1& A) { return A.sqr(); }

darr1 sqrt(const darr1& A) { return A.sqrt(); }

} // namespace arr
