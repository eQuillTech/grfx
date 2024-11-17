//sub arrays (m x n) - P. Ahrenkiel

#ifndef _ARR2SUB_
#define _ARR2SUB_

#ifndef _ARR1_
#include "arr1.hpp"
#endif

namespace arr {
    template<class data_type>
    class arr2;

//
    template<class data_type>
    class arr2sub {
    private:

    protected:
        arr2<data_type> *m_a;
        std::size_t m_iRow, m_iCol;
        std::size_t m_nRows, m_nCols;

    public:
        arr2sub(arr2<data_type> *a, const std::size_t iRow, const std::size_t iCol, const std::size_t nRows,
                const std::size_t nCols);

        void operator=(const arr2sub<data_type> &A);

        void operator=(const arr2<data_type> &A);

        arr2sub(const arr2sub<data_type> &A);

        ~arr2sub();

        arr2<data_type> *data() const { return m_a; }

        std::size_t index(const std::size_t i) const { return (i == 0) ? m_iRow : m_iCol; }

        std::size_t size(const std::size_t i) const { return (i == 0) ? m_nRows : m_nCols; }

        data_type &at(const std::size_t i, const std::size_t j);

        data_type at(const std::size_t i, const std::size_t j) const;

        data_type &operator()(const std::size_t i, const std::size_t j) { return at(i, j); }

        data_type operator()(const std::size_t i, const std::size_t j) const { return at(i, j); }

        void operator=(const data_type &x);
    };

}

#include "../sources/arr2sub.tem"

#endif
