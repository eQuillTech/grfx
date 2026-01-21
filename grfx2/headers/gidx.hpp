//graphics indices - P. Ahrenkiel

#ifndef _GIDX_
#define _GIDX_

#include "CoreGraphics/CoreGraphics.h"

#include "arr.hpp"

class gidx
{
protected:
	std::size_t m_i,m_j;

public:
	gidx(){}
	gidx(const std::size_t ip,const std::size_t jp){m_i=ip;m_j=jp;}
	gidx(const arr::uint1 &a);

	std::size_t& i(){return m_i;}
	std::size_t& j(){return m_j;}

	std::size_t& operator()(const std::size_t k){return (k==0)?m_i:m_j;}
	const std::size_t& operator()(const std::size_t k) const{return (k==0)?m_i:m_j;}

	std::size_t const& i() const{return m_i;}
	std::size_t const& j() const{return m_j;}

	static const gidx zeroI,xI,yI;

	friend std::ostream& operator<<(std::ostream &os,const gidx &I);
};



typedef arr::arr1<gidx> gidx_arr1;

#endif
