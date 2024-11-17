// bool arrays (m x n)- P. Ahrenkiel

#ifndef _BARR2_
#define _BARR2_

#include <iostream>

#ifndef _ARR2_
#include "arr2.hpp"
#endif

namespace arr {
class barr2slice;

class barr2sub;

typedef arr2<bool> bool_arr2;

//
class barr2 : public bool_arr2 {
private:
	
public:
	barr2(const std::size_t N0 = 0, const std::size_t N1 = 0, const bool *a = NULL) : bool_arr2(N0, N1, a) {}
	barr2(const bool_arr2 &A) : bool_arr2(A.size(0), A.size(1), A.data()) {}
	barr2(const barr2slice &A);
	barr2(const barr2sub &A);
	
	barr2 operator|(const barr2 &b) const;
	
	barr2 operator&(const barr2 &b) const;
	
	barr2 operator=(const bool &x) { return bool_arr2::operator=(x); }
	barr2 &operator|=(const barr2 &b);
	barr2 &operator&=(const barr2 &b);
	
	bool hasTrue() const;
	bool hasFalse() const;
	
	using bool_arr2::operator();
	
	barr2slice slice(const std::size_t iDim, const std::size_t iIndex);
	barr2slice row(const std::size_t iRow);
	barr2slice col(const std::size_t iCol);
	
	using bool_arr2::irow;
	using bool_arr2::icol;
	
	barr2sub sub(const std::size_t iRow, const std::size_t iCol, const std::size_t nRows, const std::size_t nCols);
	
	barr2sub
	operator()(const std::size_t iRow, const std::size_t iCol, const std::size_t nRows, const std::size_t nCols);
	
	friend std::ostream &operator<<(std::ostream &os, const barr2 &A);
	
	static barr2 zero(const size_t m, const size_t n);
	static barr2 ident(const size_t m, const size_t n);
};
}
#endif
