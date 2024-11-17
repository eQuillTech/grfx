//graphics coordinates - P. Ahrenkiel

#include <cstdlib>
#include <math.h>
#include "CoreGraphics/CoreGraphics.h"

#include "tlbx.hpp"
#include "grfx.hpp"

using namespace std;

//
gcrd::operator darr1() const
{
	darr1 d(2);
	d(0)=m_x;d(1)=m_y;
	return d;
}

//
gcrd::gcrd(const darr1 &d)
{
	if(d.size()==2)
	{
		x()=d(0);
		y()=d(1);
	}
	else
		arr_err=-1;
}

double& gcrd::operator()(const size_t i)
{
	switch(i)
	{
		case 0:
		return x();
		
		case 1:
		default:
		return y();
	}
}

double const& gcrd::operator()(const size_t i) const
{
	switch(i)
	{
		case 0:
		return x();
		
		case 1:
		default:
		return y();
	}
}
