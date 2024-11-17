//array slices (n) - P. Ahrenkiel

#ifndef _ARR2SLICE_
#define _ARR2SLICE_

#ifndef _ARR1_
#include "arr1.hpp"
#endif

namespace arr {
    template<class data_type>
    class arr1;

    template<class data_type>
    class arr2;

//
    template<class data_type>
    class arr2slice {
    private:

    protected:
        arr2<data_type> *m_a;
        std::size_t m_iDim;
        std::size_t m_iIndex;

    public:
        arr2slice(arr2<data_type> *a, const std::size_t iDim, const std::size_t iIndex);
        arr2slice(const arr2slice<data_type> &A);
        ~arr2slice();

        void operator=(const arr2slice<data_type> A);
        void operator=(const arr1<data_type> &A);

        arr2<data_type> *data() const { return m_a; }

        std::size_t dim() const { return m_iDim; }
        std::size_t index() const { return m_iIndex; }

        data_type &at(const std::size_t i);
        data_type at(const std::size_t i) const;

        data_type &operator()(const std::size_t i) { return at(i); }
        data_type operator()(const std::size_t i) const { return at(i); }

        std::size_t size() const;

        friend std::ostream &operator<<(std::ostream &os, const arr2slice<data_type> &A);
    };
}

#include "../sources/arr2slice.tem"

#endif
