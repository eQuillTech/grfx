//graphics lines - P. Ahrenkiel

#include <cstdlib>
#include <math.h>
#include <CoreGraphics/CoreGraphics.h>

#include "tlbx.hpp"
#include "grfx.hpp"

const glne3 glne3::zeroL(pnt3::Po,vtr3::Vo);

//
glne3 glne3::operator+=(const Vtr &V)
{
	return *this=*this+V;
}

//
glne3 glne3::operator-=(const Vtr &V)
{
	return *this=*this-V;
}

//
glne3 glne3::operator*=(double x)
{
	return *this=x*(*this);
	}
	
//
glne3 glne3::operator/=(double x)
{
	return *this=(*this)/x;
	}

//
glne3 glne3::operator+(const Vtr &V) const
{
	glne3 L(*this);
	L.P()+=V;
	return L;
}

//
glne3 glne3::operator-(const Vtr &V) const
{
	return *this+(-V);
}

//
glne3 operator*(double x,const glne3 &L)
{
	Pnt P=pnt3::Po+x*(L.P()-pnt3::Po);
	Vtr V=x*L.V();
	return glne3(P,V);
}

//
glne3 glne3::operator/(double x) const
{
	return (1./x)*(*this);
}

//
glne3 glne3::map(const gfrm3 &newF,const gfrm3 &oldF) const
{
	Pnt startP=start();
	Pnt stopP=stop();
	startP=Gpnt3(startP).map(newF,oldF);
	stopP=Gpnt3(stopP).map(newF,oldF);
	return glne3(startP,stopP);
}

//
double glne3::length() const
{
	return len(V());
}

//
Pnt glne3::closestPoint(const Pnt &P) const
{
	Pnt A=start();
	Pnt B=stop();
	Vtr AB=B-A,AC=P-A;
	double t=dot(AC,AB)/dot(AB,AB);
	if(t<0.)t=0.;
	if(t>1.)t=1.;
	return A+t*AB;
}

//
double glne3::distTo(const Pnt &P) const
{
	return len(P-closestPoint(P));
}

//
Pnt glne3::center() const
{
	return P()+V()/2.;
}

//
bool glne3::intersects(const glne3 &L)
{
/*	Pnt pA=start();
	Pnt pB=stop();
	Pnt pC=l.start();
	Pnt pD=l.stop();
	
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
Pnt glne3::intersection(const glne3 &L)
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
	return Pnt::Po;
}

//
bool glne3::intersects(const glne3 &L,Pnt &intP)
{
	if(intersects(L))
	{
		intP=intersection(L);
		return true;
	}
	return false;
}

