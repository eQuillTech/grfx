//graphics indices - P. Ahrenkiel

#include <cstdlib>

#include "uint1.hpp"
#include "gidx.hpp"

const gidx gidx::zeroI(0.,0.);
const gidx gidx::xI(1.,0.);
const gidx gidx::yI(0.,1.);

gidx::gidx(const arr::uint1 &a)
{
	if(a.size()==2)
	{
		m_i=a(0);
		m_j=a(1);
	}
	else
		arr::err=-1;
}

std::ostream& operator<<(std::ostream &os,const gidx &I)
{
	os<<"("<<I.i()<<","<<I.j()<<")";
	return os;
}


