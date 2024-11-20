//graphics points - P. Ahrenkiel

#include <cstdlib>
#include <math.h>
#include "CoreGraphics/CoreGraphics.h"

#include "tlbx.hpp"
#include "grfx2.hpp"
#include "grfx3.hpp"

using namespace std;
	
//
gpnt3 gpnt3::map(const gfrm3 &newF,const gfrm3 &oldF) const
{
	double scaleX=newF.width()/oldF.width();
	double scaleY=newF.depth()/oldF.depth();
	double scaleZ=newF.height()/oldF.height();
	
	double offsetX=newF.left()-scaleX*oldF.left();
	double offsetY=newF.front()-scaleY*oldF.front();
	double offsetZ=newF.bottom()-scaleZ*oldF.bottom();

	gpnt3 P;
	P.x()=scaleX*x()+offsetX;
	P.y()=scaleY*y()+offsetY;
	P.z()=scaleZ*z()+offsetZ;
	
	return P;
}

//
ostream& operator<<(ostream &os,const gpnt3 &P)
{
	os<<"("<<P.x()<<","<<P.y()<<","<<P.z()<<")";
	return os;
}



