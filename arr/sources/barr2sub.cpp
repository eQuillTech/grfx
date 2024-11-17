//bool subarrays (m x n) - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "arr.hpp"

namespace arr {

//
    barr2::barr2(const barr2sub &A) : bool_arr2(A) {}

//
    barr2sub
    barr2::sub(const std::size_t iRow, const std::size_t iCol, const std::size_t nRows, const std::size_t nCols) {
        return bool_arr2::sub(iRow, iCol, nRows, nCols);
    }

//
    barr2sub barr2::operator()(const std::size_t iRow, const std::size_t iCol, const std::size_t nRows,
                               const std::size_t nCols) {
        return sub(iRow, iCol, nRows, nCols);
    }

//
    void barr2sub::operator=(const barr2 &A) {
        if ((size(0) != A.size(0)) || (size(1) != A.size(1)))return;
        for (std::size_t i = 0; i < size(0); i++)
            for (std::size_t j = 0; j < size(1); j++)
                at(i, j) = A(i, j);
    }

//
    void barr2sub::operator|=(const barr2 &A) {
        if ((size(0) != A.size(0)) || (size(1) != A.size(1)))return;
        for (std::size_t i = 0; i < size(0); i++)
            for (std::size_t j = 0; j < size(1); j++)
                at(i, j) |= A(i, j);
    }

//
    void barr2sub::operator&=(const barr2 &A) {
        if ((size(0) != A.size(0)) || (size(1) != A.size(1)))return;
        for (std::size_t i = 0; i < size(0); i++)
            for (std::size_t j = 0; j < size(1); j++)
                at(i, j) &= A(i, j);
    }

//
    void barr2sub::operator=(const bool &x) {
        for (std::size_t i = 0; i < size(0); i++)
            for (std::size_t j = 0; j < size(1); j++)
                at(i, j) = x;
    }
}