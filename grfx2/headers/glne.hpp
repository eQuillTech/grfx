//graphics line segments - P. Ahrenkiel

#ifndef _GLNE_
#define _GLNE_

#include "CoreGraphics/CoreGraphics.h"

#include "weiss.hpp"
#include "Grfx_defs.hpp"

#ifndef _GPNT_
#include "gpnt.hpp"
#endif

#ifndef _GRCT_
#include "grct.hpp"
#endif

class glne:public Gfgr
{
private:
	gpnt _pStart;
	gvtr _v;
	
public:
	glne(const gpnt p=pnt2::Po,const gvtr v=Vtr2::Vo):_pStart(p),_v(v){}
	glne(const gpnt &pStart,const gpnt &pStop):glne(pStart,pStop-pStart){}
	glne(double x0,double y0,double x1,double y1):glne(gpnt(x0,y0),gvtr(x1-x0,y1-y0)){}

	gpnt& P(){return _pStart;}
	gvtr& V(){return _v;}
	
	gpnt const& P() const{return _pStart;}
	gvtr const& V() const{return _v;}

	gpnt start() const{return P();}
	gpnt stop() const{return P()+V();}

	glne operator+() const{return *this;}
	glne operator-() const{return glne(pnt2::Po+(pnt2::Po-_pStart),-_v);}

	glne operator/(double x) const;
	glne operator+=(const gvtr &V);
	glne operator-=(const gvtr &V);
	glne operator*=(double x);
	glne operator/=(double x);

	glne operator+(const gvtr &V) const;
	glne operator-(const gvtr &V) const;

	bool clip(const Gfrm &fClip,glne &lDest) const;
	glne map(const Gfrm &fNew,const Gfrm &fOld) const;

	gpnt closestPoint(const gpnt &p) const;
	double distTo(const gpnt &p) const;
	double length() const;
	gpnt center() const;

	bool intersects(const glne &l);
	gpnt intersection(const glne &l);
	bool intersects(const glne &l,gpnt &Pint);
	
	friend glne operator*(double x,const glne &l);

	void doStroke(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF) const override;

};

double length(const glne &l);
extern glne zeroL;
#endif
