//graphics points - P. Ahrenkiel

#ifndef _GPNT3_
#define _GPNT3_

#include "CoreGraphics/CoreGraphics.h"

#include "dbl1.hpp"
#include "pnt3.hpp"

class gfrm3;

class gpnt3:public pnt3
{
public:
	gpnt3(double x=0.,double y=0.,double z=0.);
	gpnt3(const pnt3 &P);
	gpnt3(const arr::dbl1 &A);

	gpnt3 map(const gfrm3 &newF,const gfrm3 &oldF) const;
	
	friend std::ostream& operator<<(std::ostream &os,const gpnt3 &P);
};

typedef arr::arr1<gpnt3> gpnt3_arr1;

#endif
