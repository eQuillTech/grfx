//graphics frames - P. Ahrenkiel

#ifndef _GFRM_
#define _GFRM_

#include "CoreGraphics/CoreGraphics.h"
#include "weiss.hpp"

typedef vtr2 gvtr;

#ifndef _GPNT_
#include "gpnt.h"
#endif

//predef
class gcmr;

class gfrm :public gfgr
{
private:
	gpnt m_bottomLeftP;
	gvtr m_diagV;
	//double m_top,m_left,m_bottom,m_right;

public:
	//gfrm (){}
	gfrm (const gpnt& tl,const gvtr& d);
	gfrm (const double t=0.,const double l=0.,const double b=0.,const double r=0.);
	gfrm (const gpnt& tl,const gpnt& br);
	gfrm (const CGRect& R);

	double top(){return (m_bottomLeftP+m_diagV).y();}
	double left(){return m_bottomLeftP.x();}
	double &bottom(){return m_bottomLeftP.y();}
	double &right(){return (m_bottomLeftP+m_diagV).x();}
	double &width(){return m_diagV.x();}
	double &height(){return m_diagV.y();}
	gpnt &bottomLeft(){return m_bottomLeftP;}
	gvtr &diag(){return m_diagV;}

	double const top() const{return (m_bottomLeftP+m_diagV).y();}
	double const left() const{return m_bottomLeftP.x();}
	double const bottom() const{return m_bottomLeftP.y();}
	double const right() const{return (m_bottomLeftP+m_diagV).x();}
	gpnt const &bottomLeft() const{return m_bottomLeftP;}
	gvtr const &diag() const{return m_diagV;}
	double const width() const{return m_diagV.x();}
	double const height() const{return m_diagV.y();}
	
	bool operator==(const gfrm  &f) const;
	
	gfrm  operator+(const gvtr &v) const;
	gfrm  operator-(const gvtr &v) const;
	gfrm  operator/(const double x) const;

	gfrm  operator+=(const gvtr &v);
	gfrm  operator-=(const gvtr &v);
	gfrm  operator*=(const double x);
	gfrm  operator/=(const double x);
	//gfrm  set(const gfrm  &r);
	
	gfrm  map(const gfrm  &fNew,const gfrm  &fOld) const;
	CGRect map(const CGRect &Rframe,const gfrm  &frameF) const;
	gpnt map(const CGPoint &P,const CGRect &Rframe) const;
	gfrm  map(const CGRect &Rframe,const CGRect &R) const;
	double map(const double d,const CGRect &Rframe) const;
	bool isIn(const gfrm  &f) const;
	bool overlaps(const gfrm  &f) const;
	friend gfrm  operator*(const double x,const gfrm  &f);
	void move(gvtr &v,const gfrm  &fBound) const;
	gfrm  alter() const;
	//fl_err read(tfl &T);
//	fl_err write(tfl &T);
	bool isIn(const gpnt &p) const;
	
	//
	gpnt center() const{return m_bottomLeftP+m_diagV/2.;}

	gpnt topRight() const{return gpnt(right(),top());}
	gpnt topLeft() const{return gpnt(left(),top());}
	gpnt bottomRight() const{return gpnt(right(),bottom());}
	gpnt centerLeft() const{return gpnt(left(),centerY());}
	gpnt centerRight() const{return gpnt(right(),centerY());}
	gpnt topCenter() const{return gpnt(centerX(),top());}
	gpnt bottomCenter() const{return gpnt(centerX(),bottom());}
	double centerX() const{return center().x();}
	double centerY() const{return center().y();}
	double totalSize() const{return width()+height();}
	double meanSize() const{return mth::pwr(width()*height(),0.5);}
	double halfMeanSize() const{return 0.5*meanSize();}
	gfrm  scale(const double f) const;

	double awidth() const{return fabs(width());}
	double aheight() const{return fabs(height());}

	CGRect sRect() const{return CGRectMake(left(),top(),width(),height());}
	CGSize sSize() const{return CGSizeMake(width(),height());}

	gfrm &R(){return *this;}
	const gfrm &R() const{return *this;}
	
	virtual void doFill(CGContextRef context,const CGRect &Rdest) const{}
	virtual void doStroke(CGContextRef context,const CGRect &Rdest) const{}
	virtual void doRender(CGContextRef context,const CGRect &Rdest) const{}
	virtual void doRender(CGContextRef context,const CGRect &Rdest,const CGRect &Rclip) const{}
	virtual void doRadGradient(CGContextRef context,const CGRect &Rdest,CGGradientRef grad) const{}

	void doFill(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const override;
	void doStroke(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const override;
	void doRender(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const override;
	void doRender(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF,const CGRect &Rext) const override;
	void doRadGradient(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF,CGGradientRef grad,const CGPoint &Pi,const CGPoint &Pf,const double Ri,const double Rf) const override;

	friend double width(const gfrm  &f){return f.width();}
	friend double height(const gfrm  &f){return f.height();}

	friend std::ostream& operator<<(std::ostream &os,const gfrm  &f);
	
	gfrm proj(const gcmr &cmr,const double z) const;
	gfrm invproj(const gcmr &cmr,const double z) const;
};

std::ostream& operator<<(std::ostream &os,const CGRect &R);

typedef arr::arr1<gfrm> gfrm_arr1;

extern const gfrm  unitF;
#endif
