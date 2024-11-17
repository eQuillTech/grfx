//graphics points - P. Ahrenkiel

#ifndef _GPNT3_
#define _GPNT3_

#include "CoreGraphics/CoreGraphics.h"

#include "arr.hpp"
#include "weiss.hpp"

class gfrm3;


class Gpnt3:public pnt3
{
public:
	Gpnt3(double x=0.,double y=0.,double z=0.):pnt3(x,y,z){}
	Gpnt3(const darr1 &A):pnt3(A){}
	Gpnt3(const Crd3 &C):pnt3(C){}

	Gpnt3 map(const gfrm3 &newF,const gfrm3 &oldF) const;
	
	friend std::ostream& operator<<(std::ostream &os,const Gpnt3 &P);
	
};

typedef arr1<Gpnt3> Gpnt3_arr1;

#endif
