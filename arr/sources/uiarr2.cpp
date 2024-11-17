// unsigned int arrays (m x n) - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "arr.hpp"

namespace arr {

//
uiarr2::uiarr2(const uint_arr2& A) : uint_arr2(A.size(0), A.size(1))
{
    for (size_t i = 0; i < m_nRows; i++)
        for (size_t j = 0; j < m_nCols; j++)
            at(i, j) = A(i, j);
}

//
uiarr2 uiarr2::minor(std::size_t iRow, std::size_t iCol) const
{
    uiarr2 res(m_nRows - 1, m_nCols - 1);
    size_t ip = 0;
    for (size_t i = 0; i < m_nCols; i++)
        if (i != iRow) {
            size_t jp = 0;
            for (size_t j = 0; j < m_nCols; j++)
                if (j != iCol) {
                    res(ip, jp) = at(i, j);
                    jp++;
                }
            ip++;
        }

    return res;
}

//
uiarr2 uiarr2::zero(const size_t nRows, const size_t nCols)
{
    uiarr2 res(nRows, nCols);
    res = 0;
    return res;
}

//
uiarr2 uiarr2::ident(const size_t nRows, const size_t nCols)
{
    uiarr2 A(nRows, nCols);
    for (size_t i = 0; i < nRows; i++)
        for (size_t j = 0; j < nCols; j++)
            A(i, j) = (i == j) ? 1 : 0;
    return A;
}

} // namespace arr