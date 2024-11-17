//double sub arrays (m x n) - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "arr.hpp"
#include "mth.hpp"
#include "trg.hpp"

namespace arr {

//
darr2::darr2(const darr2sub &A):double_arr2(A){}

//
darr2sub darr2::sub(const std::size_t iRow,const std::size_t iCol,const std::size_t nRows,const std::size_t nCols)
{
	return double_arr2::sub(iRow,iCol,nRows,nCols);
}

//
darr2sub darr2::operator()(const std::size_t iRow,const std::size_t iCol,const std::size_t nRows,const std::size_t nCols)
{
	return sub(iRow,iCol,nRows,nCols);
}

//
darr2 darr2sub::operator+() const
{
	return darr2(*this);
}

//
darr2 darr2sub::operator-() const
{
	return -darr2(*this);
}

//
darr2 darr2sub::operator+(const darr2sub &A) const
{
	return darr2(*this)+darr2(A);
}

//
darr2 darr2sub::operator-(const darr2sub &A) const
{
	return darr2(*this)-darr2(A);
}

//
darr2 darr2sub::operator/(const double x) const
{
	return darr2(*this)/x;
}

//
darr2 operator*(double x,const darr2sub &A)
{
	return x*darr2(A);
}

//
void darr2sub::operator=(const darr2 &A)
{
	if((size(0)!=A.size(0))||(size(1)!=A.size(1)))return;
	for(std::size_t i=0;i<m_nRows;i++)
		for(std::size_t j=0;j<m_nCols;j++)
			at(i,j)=A(i,j);
}

//
void darr2sub::operator+=(const darr2 &A)
{
	if((size(0)!=A.size(0))||(size(1)!=A.size(1)))return;
	for(std::size_t i=0;i<m_nRows;i++)
		for(std::size_t j=0;j<m_nCols;j++)
			at(i,j)+=A(i,j);
}

//
void darr2sub::operator-=(const darr2 &A)
{
	*this+=-A;
}

//
void darr2sub::operator*=(const double x)
{
	for(std::size_t i=0;i<m_nRows;i++)
		for(std::size_t j=0;j<m_nCols;j++)
			at(i,j)*=x;
}

//
void darr2sub::operator/=(const double x)
{
	*this*=1./x;
}

//
darr2 darr2sub::pwr(const double x) const
{
	darr2 A(m_nRows,m_nCols);
	for(std::size_t i=0;i<m_nRows;i++)
		for(std::size_t j=0;j<m_nCols;j++)
			A(i,j)=pow(at(i,j),x);
	return A;
}

//
void darr2sub::operator=(const double &x)
{
	for(std::size_t i=0;i<m_nRows;i++)
		for(std::size_t j=0;j<m_nCols;j++)
			at(i,j)=x;
}
}
