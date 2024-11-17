//bool array slices (n) - P. Ahrenkiel

#ifndef _BARR2SLICE_
#define _BARR2SLICE_

#include <iostream>

#ifndef _ARR2SLICE_
#include "arr2slice.hpp"
#endif

namespace arr {
class barr2;

typedef arr2slice<bool> bool_arr2slice;

//
class barr2slice : public bool_arr2slice {
private:
	
public:
	barr2slice(barr2 *A, const std::size_t iDim, const std::size_t iIndex) : bool_arr2slice(A, iDim, iIndex) {}
	barr2slice(const bool_arr2slice &A) : bool_arr2slice(A.data(), A.dim(), A.index()) {}
	
	barr2 operator|(const barr2slice &A) const;
	barr2 operator&(const barr2slice &A) const;
	
	void operator=(const barr2 &A);
	void operator|=(const barr2 &A);
	void operator&=(const barr2 &A);
	void operator|=(const bool x);
	void operator&=(const bool x);
	void operator=(const bool x);
	
	bool hasTrue() const;	
	bool hasFalse() const;
};
}
#endif
