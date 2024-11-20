//graphics points - P. Ahrenkiel

#include <cstdlib>
#include <math.h>
#include "CoreGraphics/CoreGraphics.h"

#include "tlbx.hpp"
#include "grfx2.hpp"

using namespace std;

const gpnt_arr1 nullP_arr(0);

//
bool gpnt::clip(const gfrm  &rClip,const gpnt &pOther,gpnt &pDest) const
{
	pDest=*this;
	if(pOther.x()==x())
	{
		if(y()<rClip.top())
			pDest.y()=rClip.top();
		if(y()>rClip.bottom())
			pDest.y()=rClip.bottom();
	}
	else
	{
		double m=(pOther.y()-y())/(pOther.x()-x());
		double b=y()-m*x();
		if(m==0)
		{
			if(x()<rClip.top())
				pDest.x()=rClip.top();

			if(x()>rClip.bottom())
				pDest.x()=rClip.bottom();
		}
		else
		{
			if((pDest.x()<rClip.top())&(pOther.x()>=rClip.top()))
			{
				pDest.x()=rClip.top();
				pDest.y()=m*rClip.top()+b;
			}
			
			if((pDest.x()>rClip.right())&(pOther.x()<=rClip.right()))
			{
				pDest.x()=rClip.right();
				pDest.y()=m*rClip.right()+b;
			}

			if((pDest.y()<rClip.top())&(pOther.y()>=rClip.top()))
			{
				pDest.x()=(rClip.top()-b)/m;
				pDest.y()=rClip.top();
			}
			
			if((pDest.y()>rClip.bottom())&(pOther.y()<=rClip.bottom()))
			{
				pDest.x()=(rClip.bottom()-b)/m;
				pDest.y()=rClip.bottom();
			}
		}
	}

	return rClip.isIn(pDest);
}
	
//
CGPoint gpnt::map(const CGRect &Rframe,const gfrm  &frameF) const
{
	CGPoint P;

	float Ax=frameF.width()/Rframe.size.width;
	float Ay=-frameF.height()/Rframe.size.height;

	float Bx=frameF.left()-Ax*Rframe.origin.x;
	float By=frameF.top()-Ay*Rframe.origin.y;

	float prod=Ax*Ay;
	if((prod==0.)||(isnan(prod)))
	{
		P.x=P.y=0;
	}
	else
	{
		float ax=1./Ax,ay=1./Ay;
		float bx=-Bx/Ax,by=-By/Ay;

		P.x=ax*x()+bx;
		P.y=ay*y()+by;
	}
	return P;
}

//
CGPoint gpnt::mapFrac(const CGRect &Rframe,const gfrm  &frameF) const
{
	CGPoint P=map(Rframe,frameF);
	CGPoint Pfrac;
	Pfrac.x=(P.x-Rframe.origin.x)/Rframe.size.width;
	Pfrac.y=(P.y-Rframe.origin.y)/Rframe.size.height;
	return Pfrac;
}

//
void gpnt::moveTo(CGContextRef context,const CGPoint &P)
{
	CGContextMoveToPoint(context,P.x,P.y);
}

//
void gpnt::lineTo(CGContextRef context,const CGPoint &P)
{
	CGContextAddLineToPoint(context,P.x,P.y);
}

//
void gpnt::doMoveTo(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const
{
	CGPoint P=map(Rframe,frameF);
	gpnt::moveTo(context,P);
}

//
void gpnt::doLineTo(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const
{
	CGPoint P=map(Rframe,frameF);
	gpnt::lineTo(context,P);
}

//
gpnt gpnt::map(const gfrm  &fNew,const gfrm  &fOld) const
{
	double scaleX=fNew.width()/fOld.width();
	double scaleY=fNew.height()/fOld.height();
	
	double offsetX=fNew.left()-scaleX*fOld.left();
	double offsetY=fNew.top()-scaleY*fOld.top();

	gpnt p;
	p.x()=scaleX*x()+offsetX;
	p.y()=scaleY*y()+offsetY;
	
	return p;
}

//
ostream& operator<<(ostream &os,const gpnt &p)
{
	os<<"("<<p.x()<<","<<p.y()<<")";
	return os;
}

//
ostream& operator<<(ostream &os,const CGPoint &P)
{
	os<<"("<<P.x<<","<<P.y<<")";
	return os;	
}


