//graphics indices - P. Ahrenkiel

#include <cstdlib>
#include <math.h>
#include "CoreGraphics/CoreGraphics.h"

#include "tlbx.hpp"
#include "grfx2.hpp"

const gidx zeroI(0.,0.);
const gidx xI(1.,0.);
const gidx yI(0.,1.);

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


