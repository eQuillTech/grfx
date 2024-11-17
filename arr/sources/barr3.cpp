//bool arrays (m x n) - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "arr.hpp"

namespace arr {

//static
    barr3 barr3::zero(const std::size_t n0, const std::size_t n1, const std::size_t n2) {
        barr3 res(n0, n1, n2);
        res = false;
        return res;
    }

//static
    barr3 barr3::ident(const std::size_t n0, const std::size_t n1, const std::size_t n2) {
        barr3 A(n0, n1, n2);
        for (size_t i = 0; i < n0; ++i)
            for (size_t j = 0; j < n1; ++j)
                for (size_t k = 0; k < n2; ++k)
                    A(i, j, k) = ((i == j) && (i == k)) ? true : false;
        return A;
    }

//
    bool barr3::hasTrue() const {
        for (size_t i = 0; i < m_n0; ++i)
            for (size_t j = 0; j < m_n1; ++j)
                for (size_t k = 0; k < m_n2; ++k)
                    if (at(i, j, k))return true;
        return false;
    }

//
    bool barr3::hasFalse() const {
        for (size_t i = 0; i < m_n0; ++i)
            for (size_t j = 0; j < m_n1; ++j)
                for (size_t k = 0; k < m_n2; ++k)
                    if (!at(i, j, k))return true;
        return false;
    }

}