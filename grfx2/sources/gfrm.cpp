//graphics frames - P. Ahrenkiel

#include <cstdlib>
#include <math.h>
#include "CoreGraphics/CoreGraphics.h"

#include "tlbx.hpp"
#include "grfx.hpp"

using namespace std;

const Gfrm unitF(1,-1,-1,1);

//
Gfrm::Gfrm(const gpnt& bl,const gvtr& d)
	:m_bottomLeftP(bl),m_diagV(d){}

//
Gfrm::Gfrm(const double t,const double l,const double b,const double r)
	:m_bottomLeftP(l,b),m_diagV(r-l,t-b){}

//
Gfrm::Gfrm(const gpnt& tl,const gpnt& br)
	:m_bottomLeftP(tl.x(),br.y()),m_diagV(br.x()-tl.x(),tl.y()-br.y()){}

//
Gfrm::Gfrm(const CGRect& R)
{
	m_bottomLeftP=gpnt(R.origin.x,R.origin.y);
	m_diagV=gvtr(R.size.width,R.size.height);
}
	
//
bool Gfrm::operator==(const Gfrm &r) const
{
	return (m_bottomLeftP==r.bottomLeft())&&(m_diagV==r.diag());
}

//
Gfrm Gfrm::operator+=(const gvtr &v)
{
	return *this=*this+v;
	}

//
Gfrm Gfrm::operator-=(const gvtr &v)
{
	return *this=*this-v;
	}

//
Gfrm Gfrm::operator*=(double x)
{
	return *this=x*(*this);
	}
	
//
Gfrm Gfrm::operator/=(const double x)
{
	return *this=(*this)/x;
	}

//
Gfrm Gfrm::operator+(const gvtr &v) const
{
	return Gfrm(m_bottomLeftP+v,m_diagV);
}

//
Gfrm Gfrm::operator-(const gvtr &v) const
{
	return *this+(-v);
}

//
Gfrm Gfrm::operator/(const double x) const
{
	return Gfrm(top()/x,left()/x,bottom()/x,right()/x);
}

//
bool Gfrm::isIn(const gpnt &p) const
{

	double rx=(p.x()-left())/(right()-left());
	double ry=(p.y()-bottom())/(top()-bottom());
	return (rx>=0.)&&(rx<=1.)&&(ry>=0.)&&(ry<=1.);
	}

//
bool Gfrm::isIn(const Gfrm &f) const
{
	return isIn(f.bottomLeft())&&isIn(f.topRight());
}

//
bool Gfrm::overlaps(const Gfrm &f) const
{
	double resX=sgn(f.left()-left())
		+sgn(f.left()-right())
		+sgn(f.right()-left())
		+sgn(f.right()-right());
		
	double resY=sgn(f.bottom()-bottom())
		+sgn(f.bottom()-top())
		+sgn(f.top()-bottom())
		+sgn(f.top()-top());
		
	return (fabs(resX)<3.)&&(fabs(resY)<3.);
}

//scale about center
Gfrm Gfrm::scale(const double x) const
{

	gvtr scaled_diagV=x*m_diagV;
	gpnt pBottomLeft=center()-scaled_diagV/2.;
	return Gfrm(pBottomLeft,scaled_diagV);
}

//
void Gfrm::move(gvtr &v,const Gfrm &fBound) const
{
	double fac=1.;
	if(v.y()!=0.)
	{
		double fTop=(fBound.top()-top())/v.y();
		double fBottom=(fBound.bottom()-bottom())/v.y();
		if((fTop>0.)&&(fTop<fac))fac=fTop;
		if((fBottom>0.)&&(fBottom<fac))fac=fBottom;
		
	}
	if(v.x()!=0.)
	{
		double fLeft=(fBound.left()-left())/v.x();
		double fRight=(fBound.right()-right())/v.x();
		if((fLeft>0.)&&(fLeft<fac))fac=fLeft;
		if((fRight>0.)&&(fRight<fac))fac=fRight;
	}
	v*=fac;
}

//
Gfrm Gfrm::map(const Gfrm &fNew,const Gfrm &fOld) const
{
	Gfrm rp=*this;
	rp.m_bottomLeftP=m_bottomLeftP.map(fNew,fOld);
	rp.m_diagV=topRight().map(fNew,fOld)-rp.m_bottomLeftP;
	return rp;
}
	
//
// CGRect origin is bottom-left, somehow.
//
CGRect Gfrm::map(const CGRect &Rframe,const Gfrm &frameF) const
{
	CGRect R;

	float Ax=frameF.width()/Rframe.size.width;
	float Ay=-frameF.height()/Rframe.size.height;

	float Bx=frameF.left()-Ax*Rframe.origin.x;
	float By=frameF.top()-Ay*Rframe.origin.y;

	float prod=Ax*Ay;
	if((prod==0.)||(isnan(prod)))
	{
		R.origin.x=R.origin.y=0;
		R.size.width=R.size.height=0;
	}
	else
	{
		float ax=1./Ax,ay=1./Ay;
		float bx=-Bx/Ax,by=-By/Ay;
		
		R.origin.x=ax*left()+bx;
		R.origin.y=ay*top()+by;
		
		R.size.width=ax*width();
		R.size.height=-ay*height();
	}
	return R;
}

//
gpnt Gfrm::map(const CGPoint &P,const CGRect &Rframe) const
{
	float scaleX=width()/Rframe.size.width;
	float scaleY=-height()/Rframe.size.height;
	
	gpnt p;
	p.x()=left()+scaleX*(P.x-Rframe.origin.x);
	p.y()=top()+scaleY*(P.y-Rframe.origin.y);

	return p;
}

//
Gfrm Gfrm::map(const CGRect &Rframe,const CGRect &R) const
{
	CGFloat Rtop=R.origin.y,Rbottom=Rtop+R.size.height;
	CGFloat Rleft=R.origin.x,Rright=Rleft+R.size.width;
	
	CGPoint R_topLeft,R_bottomRight;
	R_topLeft.x=Rleft;R_topLeft.y=Rtop;
	R_bottomRight.x=Rright;R_bottomRight.y=Rbottom;
	
	gpnt tl=map(R_topLeft,Rframe);
	gpnt br=map(R_bottomRight,Rframe);
	
	return Gfrm(tl,br);
}

//Scale a scalar
double Gfrm::map(const double d,const CGRect &Rframe) const
{
	return d*(Rframe.size.height+Rframe.size.width)/totalSize();
}

//
Gfrm Gfrm::alter() const
{
	return Gfrm(bottomRight(),-diag());
}

//
void Gfrm::doFill(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF) const
{
	CGRect Rdest=map(Rframe,frameF);
	doFill(context,Rdest);
}

//
void Gfrm::doStroke(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF) const
{
	CGRect Rdest=map(Rframe,frameF);
	doStroke(context,Rdest);
}

//
void Gfrm::doRender(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF) const
{
	CGRect Rdest=map(Rframe,frameF);
	doRender(context,Rdest);
}

//
void Gfrm::doRender(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF,const CGRect &Rext) const
{
	CGRect Rclip=map(Rframe,frameF);
	CGContextClipToRect(context,Rclip);
	doRender(context,Rext);
}

//
void Gfrm::doRadGradient(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF,CGGradientRef grad,const CGPoint &Pi,const CGPoint &Pf,const double ri,const double rf) const
{
	CGRect Rclip=map(Rframe,frameF);
	CGContextClipToRect(context,Rclip);
	CGFloat Ri=frameF.map(ri,Rframe);
	CGFloat Rf=frameF.map(rf,Rframe);
	//CGContextDrawLinearGradient(context,grad,PiFrac,PfFrac,0);
	CGContextDrawRadialGradient(context,grad,Pi,Ri,Pf,Rf,0);
}

//scale about origin
Gfrm operator*(const double x,const Gfrm &f)
{
	return Gfrm(gpnt(x*f.left(),x*f.bottom()),x*f.diag());
}

//
ostream& operator<<(ostream &os,const Gfrm &f)
{
	os<<"["<<f.topLeft()<<","<<f.bottomRight()<<"]";
	return os;
}

//
ostream& operator<<(ostream &os,const CGRect &R)
{
	float top=R.origin.y,bottom=R.origin.y+R.size.height;
	float left=R.origin.x,right=R.origin.x+R.size.width;
	os<<"[("<<left<<","<<top<<"),("<<right<<","<<bottom<<")]";
	return os;
}
