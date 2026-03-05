//graphics frames - P. Ahrenkiel

#ifndef _GFRM_
#define _GFRM_

#include "CoreGraphics/CoreGraphics.h"

#include "mth.hpp"

#include "idx2.hpp"
#include "ags2.hpp"

#include "gfgr.hpp"
#include "gvtr.hpp"
#include "gpnt.hpp"

class gcmr;

class gfrm:private ags2,public gfgr
{
private:
	gfrm(const ags2& A):ags2(A){}

public:
	gfrm();
	gfrm(const pnt2 coordP,const vtr2 diagV,const idx2 coordI=idx2::Imid);
	gfrm(const double t,const double l,const double b,const double r);
	gfrm(const gpnt& tl,const gpnt& br);
	gfrm(const CGRect& R);

	double left() const{return ((*this)*idx2::I00).x();}
	double bottom() const{return ((*this)*idx2::I00).y();}

	double right() const{return ((*this)*idx2::I11).x();}
	double top() const{return ((*this)*idx2::I11).y();}
	
	double width() const{return B().a()*vtr2::X;}
	double height() const{return B().b()*vtr2::Y;}
	
	gpnt origin() const{return p();}
	gvtr diag() const{return B()*idx2::I11;}

	bool operator==(const gfrm &f) const;
	
	gfrm operator+(const gvtr &v) const;
	gfrm operator-(const gvtr &v) const;
	gfrm operator/(const double x) const;

	gfrm operator+=(const gvtr &v);
	gfrm operator-=(const gvtr &v);
	gfrm operator*=(const double x);
	gfrm operator/=(const double x);
	
	gfrm map(const gfrm &fNew,const gfrm &fOld) const;
	CGRect map(const CGRect &Rframe,const gfrm &frameF) const;
	gpnt map(const CGPoint &P,const CGRect &Rframe) const;
	gfrm map(const CGRect &Rframe,const CGRect &R) const;
	double map(const double d,const CGRect &Rframe) const;
	//bool isIn(const gfrm &f) const;
	bool overlaps(const gfrm &f) const;
	friend gfrm operator*(const double x,const gfrm  &f);
	void move(gvtr &v,const gfrm  &fBound) const;
	gfrm alter() const;
	bool isIn(const gpnt &p) const;

	using ags2::isIn;
	using ags2::A;
	using ags2::operator*;
	
	gpnt coord(const double xc,const double yc) const{return (*this)*idx2(xc,yc);}
	gpnt center() const{return coord(0.5,0.5);}
	gpnt corner00() const{return coord(0.,0.);}
	gpnt corner10() const{return coord(1.,0.);}
	gpnt corner01() const{return coord(0.,1.);}
	gpnt corner11() const{return coord(1.,1.);}
	gpnt edgeCenter0Y() const{return coord(0.,0.5);}
	gpnt edgeCenter1Y() const{return coord(1.,0.5);}
	gpnt edgeCenterX0() const{return coord(0.5,0.);}
	gpnt edgeCenterX1() const{return coord(0.5,1.);}

	double totalSize() const;
	double meanSize() const;
	double halfMeanSize() const;
	gfrm scale(const double f) const;

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
