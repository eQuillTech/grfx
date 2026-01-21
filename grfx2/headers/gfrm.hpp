//graphics frames - P. Ahrenkiel

#ifndef _GFRM_
#define _GFRM_

#include "CoreGraphics/CoreGraphics.h"

#include "mth.hpp"

#include "gfgr.hpp"
#include "gvtr.hpp"
#include "gpnt.hpp"

class gcmr;

class gfrm:public gfgr
{
private:
	gpnt m_bottomLeftP;
	gvtr m_diagV;

public:
	//gfrm (){}
	gfrm(const gpnt& tl,const gvtr& d);
	gfrm(const double t=0.,const double l=0.,const double b=0.,const double r=0.);
	gfrm(const gpnt& tl,const gpnt& br);
	gfrm(const CGRect& R);

	double top();
	double left();
	double &bottom();
	double &right();
	double &width();
	double &height();
	gpnt &bottomLeft();
	gvtr &diag();

	double const top() const;
	double const left() const;
	double const bottom() const;
	double const right() const;
	gpnt const &bottomLeft() const;
	gvtr const &diag() const;
	double const width() const;
	double const height() const;
	
	bool operator==(const gfrm  &f) const;
	
	gfrm operator+(const gvtr &v) const;
	gfrm operator-(const gvtr &v) const;
	gfrm operator/(const double x) const;

	gfrm operator+=(const gvtr &v);
	gfrm operator-=(const gvtr &v);
	gfrm operator*=(const double x);
	gfrm operator/=(const double x);
	//gfrm  set(const gfrm  &r);
	
	gfrm map(const gfrm  &fNew,const gfrm  &fOld) const;
	CGRect map(const CGRect &Rframe,const gfrm  &frameF) const;
	gpnt map(const CGPoint &P,const CGRect &Rframe) const;
	gfrm map(const CGRect &Rframe,const CGRect &R) const;
	double map(const double d,const CGRect &Rframe) const;
	bool isIn(const gfrm  &f) const;
	bool overlaps(const gfrm  &f) const;
	friend gfrm  operator*(const double x,const gfrm  &f);
	void move(gvtr &v,const gfrm  &fBound) const;
	gfrm  alter() const;
	//fl_err read(tfl &T);
//	fl_err write(tfl &T);
	bool isIn(const gpnt &p) const;
	
	gpnt center() const;

	gpnt topRight() const;
	gpnt topLeft() const;
	gpnt bottomRight() const;
	gpnt centerLeft() const;
	gpnt centerRight() const;
	gpnt topCenter() const;
	gpnt bottomCenter() const;
	double centerX() const;
	double centerY() const;
	double totalSize() const;
	double meanSize() const;
	double halfMeanSize() const;
	gfrm  scale(const double f) const;

	double awidth() const;
	double aheight() const;

	CGRect sRect() const;
	CGSize sSize() const;

	gfrm &R();
	const gfrm &R() const;
	
	virtual void doFill(CGContextRef context,const CGRect &Rdest) const;
	virtual void doStroke(CGContextRef context,const CGRect &Rdest) const;
	virtual void doRender(CGContextRef context,const CGRect &Rdest) const;
	virtual void doRender(CGContextRef context,const CGRect &Rdest,const CGRect &Rclip) const;
	virtual void doRadGradient(CGContextRef context,const CGRect &Rdest,CGGradientRef grad) const;

	void doFill(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const override;
	void doStroke(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const override;
	void doRender(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const override;
	void doRender(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF,const CGRect &Rext) const override;
	void doRadGradient(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF,CGGradientRef grad,const CGPoint &Pi,const CGPoint &Pf,const double Ri,const double Rf) const override;

	friend double width(const gfrm &f);
	friend double height(const gfrm &f);

	friend std::ostream& operator<<(std::ostream &os,const gfrm &f);
	
	gfrm proj(const gcmr &cmr,const double z) const;
	gfrm invproj(const gcmr &cmr,const double z) const;
};

std::ostream& operator<<(std::ostream &os,const CGRect &R);

typedef arr::arr1<gfrm> gfrm_arr1;

extern const gfrm  unitF;
#endif
