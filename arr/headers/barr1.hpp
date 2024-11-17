//bool arrays (n) - P. Ahrenkiel

#ifndef _BARR1_
#define _BARR1_

#include <iostream>

#ifndef _ARR1_
#include "arr1.hpp"
#endif

namespace arr {
class barr2slice;

typedef arr1<bool> bool_arr1;

class barr1 : public bool_arr1 {
private:

public:
	barr1(const std::size_t N0 = 0, const bool *a = NULL) : bool_arr1(N0, a) {}

	barr1(const bool_arr1 &A) : bool_arr1(A.size(), A.data()) {}

	barr1(const barr2slice &A);

	barr1 operator=(const bool &x) { return bool_arr1::operator=(x); }

	friend std::ostream &operator<<(std::ostream &os, const barr1 &A);

	static barr1 zero(const size_t n);

	barr1 operator|(const barr1 &b) const;

	barr1 operator&(const barr1 &b) const;

	barr1 &operator|=(const barr1 &b);

	barr1 &operator&=(const barr1 &b);

	bool hasTrue() const;

	bool hasFalse() const;
};
}

#endif

