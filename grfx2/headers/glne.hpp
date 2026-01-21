//graphics line segments - P. Ahrenkiel

#ifndef _GLNE_
#define _GLNE_

#include "CoreGraphics/CoreGraphics.h"

#include "gfgr.hpp"
#include "gpnt.hpp"
#include "gvtr.hpp"

class glne:public gfgr
{
private:
	gpnt _pStart;
	gvtr _v;
	
public:
	glne(const gpnt p=pnt2::Po,const gvtr v=vtr2::Vo);
	glne(const gpnt &pStart,const gpnt &pStop);
	glne(double x0,double y0,double x1,double y1);

	gpnt& P();
	gvtr& V();
	
	gpnt const& P() const;
	gvtr const& V() const;

	gpnt start() const;
	gpnt stop() const;

	glne operator+() const;
	glne operator-() const;

	glne operator/(double x) const;
	glne operator+=(const gvtr &V);
	glne operator-=(const gvtr &V);
	glne operator*=(double x);
	glne operator/=(double x);

	glne operator+(const gvtr &V) const;
	glne operator-(const gvtr &V) const;

	bool clip(const gfrm  &fClip,glne &lDest) const;
	glne map(const gfrm  &fNew,const gfrm  &fOld) const;

	gpnt closestPoint(const gpnt &p) const;
	double distTo(const gpnt &p) const;
	double length() const;
	gpnt center() const;

	bool intersects(const glne &l);
	gpnt intersection(const glne &l);
	bool intersects(const glne &l,gpnt &Pint);
	
	friend glne operator*(double x,const glne &l);

	void doStroke(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const override;

};

double length(const glne &l);
extern glne zeroL;
#endif
