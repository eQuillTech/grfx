// usigned int arrays (n) - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "arr.hpp"

namespace arr {
//
uiarr1::uiarr1(const uint_arr1& A) : uint_arr1(A.size())
{
    for (size_t i = 0; i < m_n; i++)
        at(i) = A(i);
}

//
uiarr1::uiarr1(const darr1& A)
{
    resize(A.size());
    for (size_t i = 0; i < m_n; i++)
        at(i) = A(i);
}

} // namespace arr