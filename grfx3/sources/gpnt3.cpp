//graphics points - P. Ahrenkiel

#include <cstdlib>
#include <math.h>
#include "CoreGraphics/CoreGraphics.h"

#include "tlbx.hpp"
#include "grfx.hpp"

using namespace std;
	
//
Gpnt3 Gpnt3::map(const gfrm3 &newF,const gfrm3 &oldF) const
{
	double scaleX=newF.width()/oldF.width();
	double scaleY=newF.depth()/oldF.depth();
	double scaleZ=newF.height()/oldF.height();
	
	double offsetX=newF.left()-scaleX*oldF.left();
	double offsetY=newF.front()-scaleY*oldF.front();
	double offsetZ=newF.bottom()-scaleZ*oldF.bottom();

	Gpnt3 P;
	P.x()=scaleX*x()+offsetX;
	P.y()=scaleY*y()+offsetY;
	P.z()=scaleZ*z()+offsetZ;
	
	return P;
}

//
ostream& operator<<(ostream &os,const Gpnt3 &P)
{
	os<<"("<<P.x()<<","<<P.y()<<","<<P.z()<<")";
	return os;
}



