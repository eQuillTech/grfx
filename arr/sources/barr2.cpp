//bool arrays (m x n) - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "arr.hpp"

namespace arr {

//static
barr2 barr2::zero(const std::size_t m, const std::size_t n) {
	barr2 res(m, n);
	res = false;
	return res;
}

//static
barr2 barr2::ident(const std::size_t m, const std::size_t n) {
	barr2 A(m, n);
	for (size_t i = 0; i < m; i++)
		for (size_t j = 0; j < n; j++)
			A(i, j) = (i == j) ? true : false;
	return A;
}

//
barr2 barr2::operator|(const barr2 &b) const {
	size_t nRows = std::min(m_nRows, b.size(0));
	size_t nCols = std::min(m_nCols, b.size(1));
	barr2 res = (m_nRows < b.size(0)) ? b : *this;
	for (size_t i = 0; i < nRows; i++)
		for (size_t j = 0; j < nCols; j++)
			res(i) = at(i, j) || b(i, j);
	return res;
}

//
barr2 barr2::operator&(const barr2 &b) const {
	size_t nRows = std::min(m_nRows, b.size(0));
	size_t nCols = std::min(m_nCols, b.size(1));
	barr2 res = (m_nRows > b.size(0)) ? b : *this;
	for (size_t i = 0; i < nRows; i++)
		for (size_t j = 0; j < nCols; j++)
			res(i) = at(i, j) && b(i, j);
	return res;
}

//
barr2 &barr2::operator|=(const barr2 &b) {
	return *this = (*this) | b;
}

//
barr2 &barr2::operator&=(const barr2 &b) {
	return *this = (*this) & b;
}

//
bool barr2::hasTrue() const {
	for (size_t i = 0; i < m_nRows; i++)
		for (size_t j = 0; j < m_nCols; j++)
			if (at(i, j))return true;
	return false;
}

//
bool barr2::hasFalse() const {
	for (size_t i = 0; i < m_nRows; i++)
		for (size_t j = 0; j < m_nCols; j++)
			if (!at(i, j))return true;
	return false;
}

//friend
std::ostream &operator<<(std::ostream &os, const barr2 &A) {
	std::cout << "(";
	for (size_t i = 0; i < A.m_nRows; i++)
		for (size_t j = 0; j < A.m_nCols; j++) {
			if (i > 0)std::cout << "\t";
			if (A(i, j))std::cout << "T";
			else std::cout << "F";
		}
	std::cout << ")";
	return os;
}

}
