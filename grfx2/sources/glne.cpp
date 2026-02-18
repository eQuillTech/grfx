//graphics lines - P. Ahrenkiel

#include <cstdlib>
#include <CoreGraphics/CoreGraphics.h>

#include "glne.hpp"
#include "gpnt.hpp"
#include "gply.hpp"

glne zeroL(pnt2::origin,vtr2::zero);

glne::glne(const gpnt p,const gvtr v):_pStart(p),_v(v){}
glne::glne(const gpnt &pStart,const gpnt &pStop):glne(pStart,pStop-pStart){}
glne::glne(double x0,double y0,double x1,double y1):glne(gpnt(x0,y0),gvtr(x1-x0,y1-y0)){}

gpnt& glne::P(){return _pStart;}
gvtr& glne::V(){return _v;}

gpnt const& glne::P() const{return _pStart;}
gvtr const& glne::V() const{return _v;}

gpnt glne::start() const{return P();}
gpnt glne::stop() const{return P()+V();}

glne glne::operator+() const{return *this;}
glne glne::operator-() const{return glne(pnt2::origin+(pnt2::origin-_pStart),-_v);}
	
glne glne::operator+=(const gvtr &v)
{
	return *this=*this+v;
}

glne glne::operator-=(const gvtr &v)
{
	return *this=*this-v;
}

glne glne::operator*=(double x)
{
	return *this=x*(*this);
	}
	
glne glne::operator/=(double x)
{
	return *this=(*this)/x;
	}

glne glne::operator+(const gvtr &v) const
{
	glne l(*this);
	l.P()+=v;
	return l;
}

glne glne::operator-(const gvtr &v) const
{
	return *this+(-v);
}

glne operator*(double x,const glne &l)
{
	gpnt p=pnt2::origin+x*(l.P()-pnt2::origin);
	gvtr v=x*l.V();
	return glne(p,v);
}

glne glne::operator/(double x) const
{
	return (1./x)*(*this);
}

bool glne::clip(const gfrm  &fClip,glne &lDest) const
{
	lDest=*this;
	gpnt pStart=start();
	gpnt pStop=stop();
	gpnt pStartP=lDest.start();
	gpnt pStopP=lDest.stop();
	bool overlap=pStart.clip(fClip,pStop,pStartP);
	if(overlap)overlap=pStop.clip(fClip,pStart,pStopP);
	lDest=glne(pStartP,pStopP);
	return overlap;
}

glne glne::map(const gfrm  &fNew,const gfrm  &fOld) const
{
	gpnt pStart=start();
	gpnt pStop=stop();
	pStart=pStart.map(fNew,fOld);
	pStop=pStop.map(fNew,fOld);
	return glne(pStart,pStop);
}

double glne::length() const
{
	return len(V());
}

gpnt glne::closestPoint(const gpnt &p) const
{
	gpnt A=start();
	gpnt B=stop();
	gvtr AB=B-A,AC=p-A;
	double t=dot(AC,AB)/dot(AB,AB);
	if(t<0.)t=0.;
	if(t>1.)t=1.;
	return A+t*AB;
}

double glne::distTo(const gpnt &p) const
{
	return len(p-closestPoint(p));
}

gpnt glne::center() const
{
	return P()+V()/2.;
}

void glne::doStroke(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const
{
	CGContextSaveGState(context);
	const CGPoint Pstart=start().map(Rframe,frameF);
	const CGPoint Pstop=stop().map(Rframe,frameF);
	CGContextBeginPath(context);
	gpnt::moveTo(context,Pstart);
	gpnt::lineTo(context,Pstop);
	CGContextClosePath(context);
	CGContextStrokePath(context);
	CGContextRestoreGState(context);
}

bool glne::intersects(const glne &l)
{
	gpnt pA=start();
	gpnt pB=stop();
	gpnt pC=l.start();
	gpnt pD=l.stop();
	
	bool ABD_isCCW=triangleIsCCW(pA,pB,pD);
	bool ABC_isCCW=triangleIsCCW(pA,pB,pC);
	if(ABD_isCCW!=ABC_isCCW)
	{
		bool CDA_isCCW=triangleIsCCW(pC,pD,pA);
		bool CDB_isCCW=triangleIsCCW(pC,pD,pB);
		if(CDA_isCCW!=CDB_isCCW)
			return true;
	}
	return false;
}

gpnt glne::intersection(const glne &l)
{
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
	if(d==0.)return pnt2::origin;
	
	double x=(n2*p1-n1*p2)/d;
	double y=(m2*p1-m1*p2)/d;
	return gpnt(x,y);
}

bool glne::intersects(const glne &l,gpnt &Pint)
{
	if(intersects(l))
	{
		Pint=intersection(l);
		return true;
	}
	return false;
}

