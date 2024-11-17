//double array slices (n) - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "arr.hpp"
#include "mth.hpp"
#include "trg.hpp"

namespace arr {

//
darr1::darr1(const darr2slice &A) : double_arr1(A) {}
darr2::darr2(const darr2slice &A) : double_arr2(A) {}

//
darr2slice darr2::slice(const std::size_t iDim, const std::size_t iIndex) { return darr2slice(this, iDim, iIndex); }
darr2slice darr2::row(const std::size_t iIndex) { return darr2slice(this, 0, iIndex); }
darr2slice darr2::col(const std::size_t iIndex) { return darr2slice(this, 1, iIndex); }

//
darr2 darr2slice::operator+() const { return *this; }

//
darr2 darr2slice::operator-() const { return -darr2(*this); }

//
darr2 darr2slice::operator+(const darr2slice &A) const {
	return darr2(*this) + darr2(A);
}

//
darr2 darr2slice::operator-(const darr2slice &A) const {
	return darr2(*this) - darr2(A);
}

//
darr2 darr2slice::operator/(const double x) const {
	return darr2(*this) / x;
}

//friend
darr2 operator*(double x, const darr2slice &A) {
	return x * darr2(A);
}

//
void darr2slice::operator=(const darr2 &A) {
	switch (dim()) {
		case 0:
			for (std::size_t i = 0; i < size(); i++)
				data()->at(index(), i) = A(0, i);
			break;
			
		case 1:
			for (std::size_t i = 0; i < size(); i++)
				data()->at(i, index()) = A(i, 0);
	}
	//return *source();
}

//
void darr2slice::operator+=(const darr2 &A) {
	switch (dim()) {
		case 0:
			for (std::size_t i = 0; i < size(); i++)
				data()->at(index(), i) += A(0, i);
			break;
			
		case 1:
			for (std::size_t i = 0; i < size(); i++)
				data()->at(i, index()) += A(i, 0);
	}
	//return *source();
}

//
void darr2slice::operator-=(const darr2 &A) { *this += -A; }

//
void darr2slice::operator*=(const double x) {
	switch (dim()) {
		case 0:
			for (std::size_t i = 0; i < size(); i++)
				data()->at(index(), i) *= x;
			break;
			
		case 1:
			for (std::size_t i = 0; i < size(); i++)
				data()->at(i, index()) *= x;
	}
	//return *source();
}

//
void darr2slice::operator/=(const double x) { *this = (*this) / x; }

//
void darr2slice::operator=(const double x) {
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

//
double darr2slice::mag() { return darr1(*this).mag(); }
double darr2slice::magsqr() { return darr1(*this).mag(); }

//
darr1 darr2slice::pwr(const double x) const {
	darr1 A(size());
	for (std::size_t i = 0; i < size(); i++)
		A(i) = pow(at(i), x);
	return A;
}

darr1 darr2slice::sqr() const { return pwr(2.); }
darr1 darr2slice::sqrt() const { return pwr(0.5); }

}
