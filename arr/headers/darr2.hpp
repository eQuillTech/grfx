// double arrays (m x n) - P. Ahrenkiel

#ifndef _DARR2_
#define _DARR2_

#include <iostream>

#ifndef _ARR2_
#include "arr2.hpp"
#endif

namespace arr {
class darr1;

class barr2;

class uiarr2;

class darr2slice;

class darr2sub;

typedef arr2<double> double_arr2;

//
class darr2 : public double_arr2 {
private:
public:
	darr2(const std::size_t nRows = 0, std::size_t nCols = 0, const double* a = NULL)
	: double_arr2(nRows, nCols, a) {}
	
	darr2(const darr1& A) : double_arr2(A) {}
	darr2(const double_arr2& A) : double_arr2(A.size(0), A.size(1), A.data()) {}
	darr2(const darr2slice& A);
	darr2(const darr2sub& A);
	darr2(const uiarr2& A);
	
	darr2 operator+() const;
	darr2 operator-() const;
	darr2 operator+(const darr2& A) const;
	darr2 operator-(const darr2& A) const;
	darr2 operator/(double x) const;
	
	darr2 operator+=(const darr2& A);
	darr2 operator-=(const darr2& A);
	
	darr2 operator=(const double& x) { return double_arr2::operator=(x); }
	darr2 operator*=(double x);
	darr2 operator/=(double x);
	
	darr1 operator*(const darr1& A) const;
	darr2 operator*(const darr2& A) const;
	
	friend darr2 operator*(double x, const darr2& A);
	friend darr2 operator*(double x, const darr2slice& A);
	
	darr2 pwr(const double x) const;
	darr2 sqr() const;
	darr2 sqrt() const;
	
	bool isSquareSymm() const;
	
	darr2 minor(const std::size_t m, const std::size_t n) const { return double_arr2::minor(m, n); }
	darr2 T() const { return double_arr2::T(); }
	darr2 inv() const;
	darr1 diag() const;
	
	darr2 pseudoInvLeft() const;
	darr2 pseudoInvRight() const;
	darr2 dampedPseudoInvLeft(double lambda) const;
	darr2 cofactor() const;
	darr2 adjugate() const;
	double trace() const;
	double det() const;
	double diagProd() const;
	darr2 makePivotable(bool& isSingular) const;
	darr2 upper(bool& isSingular) const;
	darr2 Householder(const size_t i) const;
	darr2 Householder(const size_t iRow, const size_t jCol) const;
	darr2 upperTriang(darr2& P) const;
	darr2 upperBidiag(darr2& U, darr2& V) const;
	darr2 tridiag(darr2& P) const;
	bool PLU(darr2& P, darr2& L, darr2& U) const;
	darr2 QR(darr2& Q) const;
	bool diagSymm(darr2& s, darr2& v) const;
	darr2 diagSymm(darr2& v) const;
	bool SVD(darr2& u, darr2& s, darr2& v) const;
	bool SVDred(darr2& u, darr2& s, darr2& v, double fac) const;
	darr2 pseudoInv(double fac) const;
	darr2 rowEschelon() const;
	darr2 span() const;
	darr2 nullspace() const;
	
	using double_arr2::operator();
	using double_arr2::icol;
	using double_arr2::irow;
	
	darr2slice slice(const std::size_t iDim, const std::size_t iIndex);
	darr2slice row(const std::size_t iRow);
	darr2slice col(const std::size_t iCol);
	darr2sub sub(const std::size_t iRow,
							 const std::size_t iCol,
							 const std::size_t nRows,
							 const std::size_t nCols);
	
	darr2sub operator()(const std::size_t iRow,
											const std::size_t iCol,
											const std::size_t nRows,
											const std::size_t nCols);
	
	double findAngle(const size_t i, const size_t j, double& ang) const;
	double sum() const;
	double sumSqr() const;
	double sumOffDiag() const;
	
	static darr2 zero(const size_t m, const size_t n);
	static darr2 ident(const size_t m, const size_t n);
	static darr2 rot(const size_t iRow, const size_t jCol, double ang, size_t n);
	
	void rotR(const size_t iCol, const size_t jCol, double ang);
	void rotL(const size_t iRow, const size_t jRow, double ang);
	darr2 zero() { return *this = darr2::zero(m_nRows, m_nCols); }
	darr2 ident() { return *this = darr2::ident(m_nRows, m_nCols); }
	
	static bool showOutput;
};

darr2 pwr(const darr2& A, const double x);
darr2 sqr(const darr2& A);
darr2 sqrt(const darr2& A);
} // namespace arr

#endif
