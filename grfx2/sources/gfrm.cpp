//graphics frames - P. Ahrenkiel

#include <cstdlib>
#include "CoreGraphics/CoreGraphics.h"

#include "gpnt.hpp"
#include "gvtr.hpp"
#include "gcmr.hpp"
#include "gfrm.hpp"

const gfrm unitF(1,-1,-1,1);

gfrm::gfrm(const gpnt& bl,const gvtr& d)
	:m_bottomLeftP(bl),m_diagV(d){}

gfrm::gfrm(const double t,const double l,const double b,const double r)
	:m_bottomLeftP(l,b),m_diagV(r-l,t-b){}

gfrm::gfrm(const gpnt& tl,const gpnt& br)
	:m_bottomLeftP(tl.x(),br.y()),m_diagV(br.x()-tl.x(),tl.y()-br.y()){}

gfrm::gfrm(const CGRect& R)
{
	m_bottomLeftP=gpnt(R.origin.x,R.origin.y);
	m_diagV=gvtr(R.size.width,R.size.height);
}

double gfrm::top(){return (m_bottomLeftP+m_diagV).y();}
double gfrm::left(){return m_bottomLeftP.x();}
double &gfrm::bottom(){return m_bottomLeftP.y();}
double &gfrm::right(){return (m_bottomLeftP+m_diagV).x();}
double &gfrm::width(){return m_diagV.x();}
double &gfrm::height(){return m_diagV.y();}
gpnt &gfrm::bottomLeft(){return m_bottomLeftP;}
gvtr &gfrm::diag(){return m_diagV;}

double const gfrm::top() const{return (m_bottomLeftP+m_diagV).y();}
double const gfrm::left() const{return m_bottomLeftP.x();}
double const gfrm::bottom() const{return m_bottomLeftP.y();}
double const gfrm::right() const{return (m_bottomLeftP+m_diagV).x();}
gpnt const &gfrm::bottomLeft() const{return m_bottomLeftP;}
gvtr const &gfrm::diag() const{return m_diagV;}
double const gfrm::width() const{return m_diagV.x();}

bool gfrm::operator==(const gfrm  &r) const
{
	return (m_bottomLeftP==r.bottomLeft())&&(m_diagV==r.diag());
}

gfrm gfrm::operator+=(const gvtr &v)
{
	return *this=*this+v;
	}

gfrm gfrm::operator-=(const gvtr &v)
{
	return *this=*this-v;
	}

gfrm gfrm::operator*=(double x)
{
	return *this=x*(*this);
}
	
gfrm gfrm::operator/=(const double x)
{
	return *this=(*this)/x;
}

gfrm gfrm::operator+(const gvtr &v) const
{
	return gfrm (m_bottomLeftP+v,m_diagV);
}

gfrm gfrm::operator-(const gvtr &v) const
{
	return *this+(-v);
}

gfrm gfrm::operator/(const double x) const
{
	return gfrm (top()/x,left()/x,bottom()/x,right()/x);
}

bool gfrm::isIn(const gpnt &p) const
{

	double rx=(p.x()-left())/(right()-left());
	double ry=(p.y()-bottom())/(top()-bottom());
	return (rx>=0.)&&(rx<=1.)&&(ry>=0.)&&(ry<=1.);
}

bool gfrm::isIn(const gfrm  &f) const
{
	return isIn(f.bottomLeft())&&isIn(f.topRight());
}

bool gfrm::overlaps(const gfrm  &f) const
{
	double resX=mth::sgn(f.left()-left())
		+mth::sgn(f.left()-right())
		+mth::sgn(f.right()-left())
		+mth::sgn(f.right()-right());
		
	double resY=mth::sgn(f.bottom()-bottom())
		+mth::sgn(f.bottom()-top())
		+mth::sgn(f.top()-bottom())
		+mth::sgn(f.top()-top());
		
	return (fabs(resX)<3.)&&(fabs(resY)<3.);
}

//scale about center
gfrm gfrm::scale(const double x) const
{

	gvtr scaled_diagV=x*m_diagV;
	gpnt pBottomLeft=center()-scaled_diagV/2.;
	return gfrm (pBottomLeft,scaled_diagV);
}

void gfrm::move(gvtr &v,const gfrm  &fBound) const
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

gfrm gfrm::map(const gfrm  &fNew,const gfrm  &fOld) const
{
	gfrm  rp=*this;
	rp.m_bottomLeftP=m_bottomLeftP.map(fNew,fOld);
	rp.m_diagV=topRight().map(fNew,fOld)-rp.m_bottomLeftP;
	return rp;
}
	
// CGRect origin is bottom-left, somehow.
CGRect gfrm::map(const CGRect &Rframe,const gfrm  &frameF) const
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
gpnt gfrm::map(const CGPoint &P,const CGRect &Rframe) const
{
	float scaleX=width()/Rframe.size.width;
	float scaleY=-height()/Rframe.size.height;
	
	gpnt p;
	p.x()=left()+scaleX*(P.x-Rframe.origin.x);
	p.y()=top()+scaleY*(P.y-Rframe.origin.y);

	return p;
}

//
gfrm gfrm::map(const CGRect &Rframe,const CGRect &R) const
{
	CGFloat Rtop=R.origin.y,Rbottom=Rtop+R.size.height;
	CGFloat Rleft=R.origin.x,Rright=Rleft+R.size.width;
	
	CGPoint R_topLeft,R_bottomRight;
	R_topLeft.x=Rleft;R_topLeft.y=Rtop;
	R_bottomRight.x=Rright;R_bottomRight.y=Rbottom;
	
	gpnt tl=map(R_topLeft,Rframe);
	gpnt br=map(R_bottomRight,Rframe);
	
	return gfrm (tl,br);
}

//Scale a scalar
double gfrm::map(const double d,const CGRect &Rframe) const
{
	return d*(Rframe.size.height+Rframe.size.width)/totalSize();
}

//
gfrm gfrm::alter() const
{
	return gfrm (bottomRight(),-diag());
}

//
void gfrm::doFill(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const
{
	CGRect Rdest=map(Rframe,frameF);
	doFill(context,Rdest);
}

//
void gfrm::doStroke(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const
{
	CGRect Rdest=map(Rframe,frameF);
	doStroke(context,Rdest);
}

//
void gfrm::doRender(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const
{
	CGRect Rdest=map(Rframe,frameF);
	doRender(context,Rdest);
}

//
void gfrm::doRender(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF,const CGRect &Rext) const
{
	CGRect Rclip=map(Rframe,frameF);
	CGContextClipToRect(context,Rclip);
	doRender(context,Rext);
}

void gfrm::doRadGradient(CGContextRef context,const CGRect &Rframe,const gfrm &frameF,CGGradientRef grad,const CGPoint &Pi,const CGPoint &Pf,const double ri,const double rf) const
{
	CGRect Rclip=map(Rframe,frameF);
	CGContextClipToRect(context,Rclip);
	CGFloat Ri=frameF.map(ri,Rframe);
	CGFloat Rf=frameF.map(rf,Rframe);
	//CGContextDrawLinearGradient(context,grad,PiFrac,PfFrac,0);
	CGContextDrawRadialGradient(context,grad,Pi,Ri,Pf,Rf,0);
}

//scale about origin
gfrm operator*(const double x,const gfrm &f)
{
	return gfrm (gpnt(x*f.left(),x*f.bottom()),x*f.diag());
}

std::ostream& operator<<(std::ostream &os,const gfrm &f)
{
	os<<"["<<f.topLeft()<<","<<f.bottomRight()<<"]";
	return os;
}

std::ostream& operator<<(std::ostream &os,const CGRect &R)
{
	float top=R.origin.y,bottom=R.origin.y+R.size.height;
	float left=R.origin.x,right=R.origin.x+R.size.width;
	os<<"[("<<left<<","<<top<<"),("<<right<<","<<bottom<<")]";
	return os;
}

//friend
gfrm gfrm::proj(const gcmr &cmr,const double z) const
{
	if(z==cmr.m_aperZ)
		return 0.*unitF;
	double mag=(z-cmr.m_aperZ)/(cmr.m_plateZ-cmr.m_aperZ);
	gvtr dV=cmr.m_aperP-pnt2::Po;
	return mag*(*this-dV)+dV;
}

gpnt gfrm::center() const{return m_bottomLeftP+m_diagV/2.;}

gpnt gfrm::topRight() const{return gpnt(right(),top());}
gpnt gfrm::topLeft() const{return gpnt(left(),top());}
gpnt gfrm::bottomRight() const{return gpnt(right(),bottom());}
gpnt gfrm::centerLeft() const{return gpnt(left(),centerY());}
gpnt gfrm::centerRight() const{return gpnt(right(),centerY());}
gpnt gfrm::topCenter() const{return gpnt(centerX(),top());}
gpnt gfrm::bottomCenter() const{return gpnt(centerX(),bottom());}
double gfrm::centerX() const{return center().x();}
double gfrm::centerY() const{return center().y();}
double gfrm::totalSize() const{return width()+height();}
double gfrm::meanSize() const{return mth::pwr(width()*height(),0.5);}
double gfrm::halfMeanSize() const{return 0.5*meanSize();}

double gfrm::awidth() const{return fabs(width());}
double gfrm::aheight() const{return fabs(height());}

CGRect gfrm::sRect() const{return CGRectMake(left(),top(),width(),height());}
CGSize gfrm::sSize() const{return CGSizeMake(width(),height());}

gfrm &gfrm::R(){return *this;}
const gfrm &gfrm::R() const{return *this;}

void gfrm::doFill(CGContextRef context,const CGRect &Rdest) const{}
void gfrm::doStroke(CGContextRef context,const CGRect &Rdest) const{}
void gfrm::doRender(CGContextRef context,const CGRect &Rdest) const{}
void gfrm::doRender(CGContextRef context,const CGRect &Rdest,const CGRect &Rclip) const{}
void gfrm::doRadGradient(CGContextRef context,const CGRect &Rdest,CGGradientRef grad) const{}

double width(const gfrm  &f){return f.width();}
double height(const gfrm  &f){return f.height();}
