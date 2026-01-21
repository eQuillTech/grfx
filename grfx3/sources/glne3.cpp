//graphics line segmentss - P. Ahrenkiel

#include <cstdlib>
#include <CoreGraphics/CoreGraphics.h>

#include "vtr3.hpp"
#include "pnt3.hpp"
#include "gfrm3.hpp"
#include "gpnt3.hpp"
#include "glne3.hpp"


const glne3 glne3::zeroL(pnt3::Po,vtr3::Vo);

glne3 glne3::operator+=(const vtr3 &V)
{
	return *this=*this+V;
}

glne3 glne3::operator-=(const vtr3 &V)
{
	return *this=*this-V;
}

glne3 glne3::operator*=(double x)
{
	return *this=x*(*this);
	}
	
//
glne3 glne3::operator/=(double x)
{
	return *this=(*this)/x;
	}

glne3 glne3::operator+(const vtr3 &V) const
{
	glne3 L(*this);
	L.P()+=V;
	return L;
}

glne3 glne3::operator-(const vtr3 &V) const
{
	return *this+(-V);
}

glne3 operator*(double x,const glne3 &L)
{
	pnt3 P=pnt3::Po+x*(L.P()-pnt3::Po);
	vtr3 V=x*L.V();
	return glne3(P,V);
}

glne3 glne3::operator/(double x) const
{
	return (1./x)*(*this);
}

glne3 glne3::map(const gfrm3 &newF,const gfrm3 &oldF) const
{
	pnt3 startP=start();
	pnt3 stopP=stop();
	startP=gpnt3(startP).map(newF,oldF);
	stopP=gpnt3(stopP).map(newF,oldF);
	return glne3(startP,stopP);
}

double glne3::length() const
{
	return len(V());
}

pnt3 glne3::closestPoint(const pnt3 &P) const
{
	pnt3 A=start();
	pnt3 B=stop();
	vtr3 AB=B-A,AC=P-A;
	double t=dot(AC,AB)/dot(AB,AB);
	if(t<0.)t=0.;
	if(t>1.)t=1.;
	return A+t*AB;
}

//
double glne3::distTo(const pnt3 &P) const
{
	return len(P-closestPoint(P));
}

//
pnt3 glne3::center() const
{
	return P()+V()/2.;
}

//
bool glne3::intersects(const glne3 &L)
{
/*	pnt3 pA=start();
	pnt3 pB=stop();
	pnt3 pC=l.start();
	pnt3 pD=l.stop();
	
	bool ABD_isCCW=triangleIsCCW(pA,pB,pD);
	bool ABC_isCCW=triangleIsCCW(pA,pB,pC);
	if(ABD_isCCW!=ABC_isCCW)
	{
		bool CDA_isCCW=triangleIsCCW(pC,pD,pA);
		bool CDB_isCCW=triangleIsCCW(pC,pD,pB);
		if(CDA_isCCW!=CDB_isCCW)
			return true;
	}
	*/
	return false;
}

//
pnt3 glne3::intersection(const glne3 &L)
{
/*
	gpnt pA=start();
	gpnt pB=stop();
	gpnt pC=l.start();
	gpnt pD=l.stop();

	double m1=pA.y()-pB.y();
	double n1=pA.x()-pB.x();
	double p1=pA.x()*pB.y()-pA.y()-pB.x();

	double m2=pC.y()-pD.y();
	double n2=pC.x()-pD.x();
	double p2=pC.x()*pD.y()-pC.y()-pD.x();

	double d=m1*n2-m2*n1;
	if(d==0.)return pnt2::Po;
	
	double x=(n2*p1-n1*p2)/d;
	double y=(m2*p1-m1*p2)/d;
*/
	return pnt3::Po;
}

//
bool glne3::intersects(const glne3 &L,pnt3 &intP)
{
	if(intersects(L))
	{
		intP=intersection(L);
		return true;
	}
	return false;
}

