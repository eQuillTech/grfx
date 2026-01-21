//graphics points - P. Ahrenkiel

#include <cstdlib>
#include "CoreGraphics/CoreGraphics.h"

#include "dbl1.hpp"
#include "gfrm3.hpp"
#include "gpnt3.hpp"

gpnt3::gpnt3(const pnt3 &P):pnt3(P){}
gpnt3::gpnt3(double x=0.,double y=0.,double z=0.):pnt3(x,y,z){}
gpnt3::gpnt3(const arr::dbl1 &A):pnt3(A){}
	
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

std::ostream& operator<<(std::ostream &os,const gpnt3 &P)
{
	os<<"("<<P.x()<<","<<P.y()<<","<<P.z()<<")";
	return os;
}



