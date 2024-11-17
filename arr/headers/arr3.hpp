// arrays (m x n) - P. Ahrenkiel

#ifndef _ARR3_
#define _ARR3_

#ifndef _ARR1_
#include "arr2.hpp"
#endif

#ifndef _ARR1_
#include "arr2.hpp"
#endif

#include <vector>

namespace arr {
//
template <class data_type>
class arr3 {
  private:
  protected:
    data_type* m_a;
    std::size_t m_n0, m_n1, m_n2;

  public:
    arr3(const std::size_t n0 = 0,
         const std::size_t n1 = 0,
         const std::size_t n2 = 0,
         const data_type* a = NULL);

    arr3(const arr3<data_type>& A); // copy constructor
    ~arr3();

    arr3<data_type>& operator=(const data_type& x);

    arr3<data_type>& operator=(const arr3<data_type>& A);

    data_type* source() const { return m_a; }

    std::vector<data_type> vect();

    std::size_t size() const { return m_n0 * m_n1 * m_n2; }

    std::size_t size(std::size_t d) const;

    void resize(const size_t n0, const size_t n1, const size_t n2);

    bool operator==(const arr3<data_type>& A) const;

    bool operator!=(const arr3<data_type>& A) const;

    bool isCube() const { return (m_n0 == m_n0) && (m_n0 == m_n1); }

    data_type& at(const std::size_t i0, const std::size_t i1, const std::size_t i2);

    data_type const& at(const std::size_t i0, const std::size_t i1, const std::size_t i2) const;

    data_type& operator()(const std::size_t i, const std::size_t j, const std::size_t k)
    {
        return at(i, j, k);
    }

    data_type const& operator()(const std::size_t i, const std::size_t j, const std::size_t k) const
    {
        return at(i, j, k);
    }
};

} // namespace arr

#include "../sources/arr3.tem"

#endif
