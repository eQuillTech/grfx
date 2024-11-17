// arrays (m x n) - P. Ahrenkiel

#ifndef _ARR2_
#define _ARR2_

#ifndef _ARR1_
#include "arr1.hpp"
#endif

#include <vector>

namespace arr {
template <class data_type>
class arr2slice;

template <class data_type>
class arr2sub;

//
template <class data_type>
class arr2 {
  private:
  protected:
    std::unique_ptr<data_type[]> m_a;
    std::size_t m_nRows, m_nCols;

  public:
    arr2(const std::size_t nRows = 0, const std::size_t nCols = 0, const data_type* a = NULL);
    arr2(const arr1<data_type>& A);
   	arr2(std::initializer_list<std::initializer_list<data_type>> A);
    arr2(const arr2<data_type>& A); // copy constructor
    arr2(const arr2slice<data_type>& A);
    arr2(const arr2sub<data_type>& A);
    ~arr2();

    arr2<data_type>& operator=(const data_type& x);
    arr2<data_type>& operator=(const arr2<data_type>& A);
    data_type* data() const { return m_a.get(); }
    std::vector<data_type> vect();
    
    std::size_t size() const { return m_nRows * m_nCols; }
    std::size_t size(std::size_t d) const;
    void resize(const size_t nRows, const size_t nCols);

    bool operator==(const arr2<data_type>& A) const;
    bool operator!=(const arr2<data_type>& A) const;

    bool isSquare() const { return m_nRows == m_nCols; }

    arr2<data_type> minor(const std::size_t m, const std::size_t n) const;
    arr1<data_type> operator()(const std::size_t i) const;
    arr2<data_type> T() const;

    arr2slice<data_type> slice(const std::size_t iDim, const std::size_t iIndex);
    arr2slice<data_type> col(const std::size_t iIndex);
    arr2slice<data_type> row(const std::size_t iIndex);
    arr2sub<data_type> sub(const std::size_t iRow,
                           const std::size_t iCol,
                           const std::size_t nRows,
                           const std::size_t nCols);

    data_type& at(const std::size_t i0, const std::size_t i1);
    data_type const& at(const std::size_t i0, const std::size_t i1) const;
    data_type& operator()(const std::size_t i, const std::size_t j) { return at(i, j); }
    data_type const& operator()(const std::size_t i, const std::size_t j) const { return at(i, j); }

    arr2sub<data_type> operator()(const std::size_t iRow,
                                  const std::size_t iCol,
                                  const std::size_t nRows,
                                  const std::size_t nCols);

    arr2<std::size_t> icol() const;
    arr2<std::size_t> irow() const;

    arr2<data_type> operator()(const arr2<std::size_t> A, const std::size_t Bi);
    arr2<data_type> operator()(const std::size_t Ai, const arr2<std::size_t> B);
    arr2<data_type> operator()(const arr2<std::size_t> A, const arr2<std::size_t> B);

    bool swapRows(const std::size_t iRow1, const std::size_t iRow2);
    bool swapCols(const std::size_t iCol1, const std::size_t iCol2);

    //
    class iterator {
        data_type* ap;

      public:
        iterator(data_type* p) : ap(p) {}

        iterator operator++()
        {
            iterator i = *this;
            ap++;
            return i;
        }

        iterator operator++(int) { return iterator(ap++); }

        iterator operator--()
        {
            iterator i = *this;
            ap--;
            return i;
        }

        iterator operator--(int) { return iterator(ap--); }

        iterator operator+(int n) const { return iterator(ap + n); }

        iterator operator-(int n) const { return iterator(ap - n); }

        iterator& operator+=(int n)
        {
            ap += n;
            return *this;
        }

        iterator& operator-=(int n)
        {
            ap -= n;
            return *this;
        }

        bool operator!=(const iterator& b) const { return ap != b.ap; }

        data_type& operator*() { return *ap; }
    };

    iterator begin() { return iterator(m_a); }

    iterator end() { return iterator(m_a + size()); }
};

template <class data_type>
std::ostream& operator<<(std::ostream& os, const arr2<data_type>& A);
} // namespace arr

#include "../sources/arr2.tem"

#endif
