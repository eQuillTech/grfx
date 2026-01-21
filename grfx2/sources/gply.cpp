//graphics polygons - P. Ahrenkiel

#include <cstdlib>
#include "CoreGraphics/CoreGraphics.h"

#include "gfrm.hpp"
#include "gply.hpp"

gply::gply(const std::size_t N0=0,gpnt* a=NULL):gpnt_arr1(0,a){}
gply::gply(const gpnt_arr1& points):gpnt_arr1(points){}

double triangleArea(gpnt pA,gpnt pB,gpnt pC)
{
	return (pB-pA).cross(pC-pA);
	//return pB.cross(pC)+pA.cross(pB)+pC.cross(pA);
}

bool triangleIsCCW(gpnt pA,gpnt pB,gpnt pC)
{
	return triangleArea(pA,pB,pC)>0.;
}

gply::gply(const gfrm & f)
{
	clear();
	append(f.bottomRight());
	append(f.topRight());
	append(f.topLeft());
	append(f.bottomLeft());
}

gply gply::operator+=(const gvtr &v)
{
	for(size_t i=0;i<size();++i)
		(*this)(i)+=v;
	return *this;
}

gply gply::operator-=(const gvtr &v)
{
	for(size_t i=0;i<size();++i)
		(*this)(i)-=v;
	return *this;
}

gply gply::operator+(const gvtr &v) const
{
	gply p=*this;
	for(size_t i=0;i<size();++i)
		p(i)+=v;
	return p;
}

gply gply::operator-(const gvtr &v) const
{
	return *this+(-v);
}

double gply::top() const
{
	double s=(*this)(0).y(),sp;
	for(size_t i=1;i<size();++i)
	{
		sp=(*this)(i).y();
		if(sp>s)s=sp;
	}
	return s;
}

double gply::left() const
{
	double s=(*this)(0).x(),sp;
	for(size_t i=1;i<size();++i)
	{
		sp=(*this)(i).x();
		if(sp<s)s=sp;
	}
	return s;
}

//
double gply::bottom() const
{
	double s=(*this)(0).y(),sp;
	for(size_t i=1;i<size();++i)
	{
		sp=(*this)(i).y();
		if(sp<s)s=sp;
	}
	return s;
}

double gply::right() const
{
	double s=(*this)(0).x(),sp;
	for(size_t i=1;i<size();++i)
	{
		sp=(*this)(i).x();
		if(sp>s)s=sp;
	}
	return s;
}

gpnt gply::center() const
{
	return gpnt((left()+right())/2.,(top()+bottom())/2.);
}

gpnt gply::topLeft() const
{
	return gpnt(left(),top());
}

gpnt gply::topRight() const
{
	return gpnt(right(),top());
}

gpnt gply::bottomLeft() const
{
	return gpnt(left(),bottom());
}

gpnt gply::bottomRight() const
{
	return gpnt(right(),bottom());
}

double gply::area() const
{
	size_t nP=size();
  double sum(0.);
  gpnt B=at(nP-1);
  for(size_t i=0;i<nP;++i)
  {
  	gpnt A=at(i);
    sum+=B.x()*A.y()-B.y()*A.x();
		B=A;
  }
  return fabs(sum)/2.;
}

//Checks if polygon is CCW
bool gply::isCCW() const
{
	return area()>0.;
}

//Checks if polygon is convex and CCW
bool gply::isConvex() const
{
	size_t nP=size();
	bool first=true,isCCW=true,res=true;
	isCCW=true;
	gpnt B=at(nP-1);
	for(size_t i=0;i<nP;++i)
	{
		gpnt A=at(i);
		for(size_t k=0;k<nP;++k)
		{
			bool dir=triangleIsCCW(A,B,cyc(k));
			if(first){isCCW=dir;first=false;}
			if(dir!=isCCW){res=false;break;}
		}
		B=A;
	}
	return res;
}

//Checks if point is in convex polygon
bool gply::isIn(const gpnt &P) const
{
	size_t iLow=0,iHigh=size();
	do
	{
		size_t iMid=(iLow+iHigh)/2;
		if(triangleIsCCW((*this)(0),(*this)(iMid),P))
			iLow=iMid;
		else
			iHigh=iMid;
	}while(iLow+1<iHigh);
	if((iLow==0)||(iHigh==size()))return false;
	return triangleIsCCW((*this)(iLow),(*this)(iHigh),P);

}

//
gpnt gply::closestPoint(const gpnt &p,glne &Lclose) const
{
	size_t nP=size();
	gpnt p0=at(nP-1);
	double d2Min=1.e12;
	bool first=true;
	gpnt D;
	for(size_t i=0;i<nP;++i)
	{
		glne L(p0,at(i));
		gpnt Dp=L.closestPoint(p);
		double d2=(Dp-p).sqrlen();
		if((d2<d2Min)||first){d2Min=d2;D=Dp;Lclose=L;first=false;}
		p0=at(i);
	}
	return D;
}

gpnt gply::closestPoint(const gpnt &p) const
{
	glne Lclose;
	return closestPoint(p,Lclose);
}

bool gply::intersection(const glne &L,gpnt &Pint,glne &Lint) const
{
	size_t nP=size();
	gpnt C=at(nP-1);
	double d2=1.e12;
	bool found(false);
	for(size_t i=0;i<nP;++i)
	{
		gpnt D(at(i));
		glne CD(C,D);
		gpnt P;
		if(CD.intersects(L,P))
		{
			gvtr BP=P-L.stop();
			double d2p=BP.sqrlen();
			if(d2p<d2){d2p=d2;Lint=CD;Pint=P;found=true;}
		}
		C=D;
	}
	return found;
}

bool gply::intersection(const glne &L,glne &Lint) const
{
	gpnt Pint;
	return intersection(L,Pint,Lint);
}

double gply::distTo(const gpnt &p) const
{
	return len(p-closestPoint(p));
}

gply gply::map(const gfrm  &fNew,const gfrm  &fOld) const
{
	gply p(*this);
	for(size_t i=0;i<size();++i)
		p(i)=p(i).map(fNew,fOld);
	return p;
}

void gply::trace(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const
{
	CGContextBeginPath(context);
	bool first=true;
	for(size_t i=0;i<size();++i)
	{
		CGPoint P=(*this)(i).map(Rframe,frameF);
		if(first)
			CGContextMoveToPoint(context,P.x,P.y);
		else
			CGContextAddLineToPoint(context,P.x,P.y);
		first=false;
	}
	CGContextClosePath(context);

}

void gply::doFill(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const
{
	trace(context,Rframe,frameF);
	CGContextFillPath(context);
}

void gply::doStroke(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const
{
	trace(context,Rframe,frameF);
	CGContextStrokePath(context);
}

std::ostream& operator<<(std::ostream &os,const gply &P)
{
	os<<"[";
	bool first=TRUE;
	for(size_t i=0;i<P.size();++i)
	{
		if(!first)
			os<<",";
		os<<P(i);
	}
	os<<"]";
	return os;
}
