//graphics line segments - P. Ahrenkiel

#ifndef _GLNE3_
#define _GLNE3_

#include "pnt3.hpp"
#include "vtr3.hpp"

class gfrm3;

class glne3
{
private:
	pnt3 _startP;
	vtr3 _extentV;
	
public:
	glne3(const pnt3 &startP=pnt3::origin,const vtr3 &extentV=vtr3::zero):_startP(startP),_extentV(extentV){}
	glne3(const pnt3 &startP,const pnt3 &stopP):glne3(startP,stopP-startP){}

	pnt3& P(){return _startP;}
	vtr3& V(){return _extentV;}
	
	pnt3 const& P() const{return _startP;}
	vtr3 const& V() const{return _extentV;}

	pnt3 start() const{return _startP;}
	pnt3 stop() const{return _startP+_extentV;}

	glne3 operator+() const{return *this;}
	glne3 operator-() const{return glne3(pnt3::origin+(pnt3::origin-_startP),-_extentV);}

	glne3 operator/(double x) const;
	glne3 operator+=(const vtr3 &V);
	glne3 operator-=(const vtr3 &V);
	glne3 operator*=(double x);
	glne3 operator/=(double x);

	glne3 operator+(const vtr3 &V) const;
	glne3 operator-(const vtr3 &V) const;

	glne3 map(const gfrm3 &newF,const gfrm3 &oldF) const;

	pnt3 closestPoint(const pnt3 &P) const;
	double distTo(const pnt3 &P) const;
	double length() const;
	pnt3 center() const;

	bool intersects(const glne3 &L);
	pnt3 intersection(const glne3 &L);
	bool intersects(const glne3 &L,pnt3 &intP);
	
	friend glne3 operator*(double x,const glne3 &L);
	
	static const glne3 zeroL;

};

double length(const glne3 &L);
#endif
