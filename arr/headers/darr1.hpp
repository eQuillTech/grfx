// double arrays (n) - P. Ahrenkiel

#ifndef _DARR1_
#define _DARR1_

#include <iostream>

namespace arr {

#ifndef _ARR1_
#include "arr1.hpp"
#endif

class darr2;

class darr2slice;

class uiarr1;

typedef arr1<double> double_arr1;

//
class darr1 : public double_arr1 {
private:
public:
	darr1(const std::size_t n = 0, const double* ap = NULL) : double_arr1(n, ap) {}
	darr1(const double_arr1& A) : double_arr1(A.size(), A.data()) {}
	darr1(const darr2slice& A);
	
	darr1 operator+() const;
	darr1 operator-() const;
	darr1 operator+(const darr1& A) const;
	darr1 operator-(const darr1& A) const;
	
	darr1 operator=(const double& x) { return double_arr1::operator=(x); }
	darr1 operator+=(const darr1& A);
	darr1 operator-=(const darr1& A);
	darr1 operator/=(double x);
	darr1 operator*=(double x);
	
	darr1 pwr(double x) const;
	darr1 sqr() const;
	darr1 sqrt() const;
	
	double dot(const darr1& A) const;
	
	darr1 operator/(double x) const;
	
	bool swap(std::size_t i1, std::size_t i2);
	darr1 sub(std::size_t i, std::size_t n) const;
	
	double mag() const;
	double sum() const;
	double sumSqr() const;
	darr1 norm() const { return (*this) / mag(); }
	
	friend darr1 norm(const darr1& A) { return A.norm(); }
	friend double mag(const darr1& A) { return A.mag(); }
	friend double sumSqr(const darr1& A) { return A.sumSqr(); }
	friend darr1 operator*(double x, const darr1& A);
	
	// predef
	darr2 T() const;
	darr2 diag() const;
	
	static darr1 zero(const size_t n);
	
	darr2 operator*(const darr2& A) const;
};

darr1 pwr(const darr1& A, const double x);
darr1 sqr(const darr1& A);
darr1 sqrt(const darr1& A);
} // namespace arr

#endif
