//bool array slices (n) - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "arr.hpp"

namespace arr {

//
barr1::barr1(const barr2slice &A) : bool_arr1(A) {}
barr2::barr2(const barr2slice &A) : bool_arr2(A) {}

//
barr2slice barr2::slice(const std::size_t iDim, const std::size_t iIndex) { return barr2slice(this, iDim, iIndex); }
barr2slice barr2::row(const std::size_t iIndex) { return barr2slice(this, 0, iIndex); }
barr2slice barr2::col(const std::size_t iIndex) { return barr2slice(this, 1, iIndex); }

//
barr2 barr2slice::operator|(const barr2slice &A) const {
	return barr2(*this) | barr2(A);
}

//
barr2 barr2slice::operator&(const barr2slice &A) const {
	return barr2(*this) & barr2(A);
}

//
void barr2slice::operator|=(const barr2 &A) {
	switch (dim()) {
		case 0:
			for (std::size_t i = 0; i < size(); i++)
				data()->at(index(), i) |= A(0, i);
			break;
			
		case 1:
			for (std::size_t i = 0; i < size(); i++)
				data()->at(i, index()) |= A(i, 0);
	}
}

//
void barr2slice::operator&=(const barr2 &A) {
	switch (dim()) {
		case 0:
			for (std::size_t i = 0; i < size(); i++)
				data()->at(index(), i) &= A(0, i);
			break;
			
		case 1:
			for (std::size_t i = 0; i < size(); i++)
				data()->at(i, index()) &= A(i, 0);
	}
}

//
void barr2slice::operator=(const bool x) {
	switch (dim()) {
		case 0:
			for (std::size_t i = 0; i < size(); i++)
				data()->at(index(), i) = x;
			break;
			
		case 1:
			for (std::size_t i = 0; i < size(); i++)
				data()->at(i, index()) = x;
	}
	//return *source();
}

}
