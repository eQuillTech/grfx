//graphics line segments - P. Ahrenkiel

#ifndef _GLNE3_
#define _GLNE3_

#include "weiss.hpp"
#include "defs.hpp"

class glne3
{
private:
	Pnt _startP;
	Vtr _extentV;
	
public:
	glne3(const Pnt &startP=pnt3::Po,const Vtr &extentV=Vtr::Vo):_startP(startP),_extentV(extentV){}
	glne3(const Pnt &startP,const Pnt &stopP):glne3(startP,stopP-startP){}

	Pnt& P(){return _startP;}
	Vtr& V(){return _extentV;}
	
	Pnt const& P() const{return _startP;}
	Vtr const& V() const{return _extentV;}

	Pnt start() const{return _startP;}
	Pnt stop() const{return _startP+_extentV;}

	glne3 operator+() const{return *this;}
	glne3 operator-() const{return glne3(pnt3::Po+(pnt3::Po-_startP),-_extentV);}

	glne3 operator/(double x) const;
	glne3 operator+=(const Vtr &V);
	glne3 operator-=(const Vtr &V);
	glne3 operator*=(double x);
	glne3 operator/=(double x);

	glne3 operator+(const Vtr &V) const;
	glne3 operator-(const Vtr &V) const;

	glne3 map(const gfrm3 &newF,const gfrm3 &oldF) const;

	Pnt closestPoint(const Pnt &P) const;
	double distTo(const Pnt &P) const;
	double length() const;
	Pnt center() const;

	bool intersects(const glne3 &L);
	Pnt intersection(const glne3 &L);
	bool intersects(const glne3 &L,Pnt &intP);
	
	friend glne3 operator*(double x,const glne3 &L);
	
	static const glne3 zeroL;

};

double length(const glne3 &L);
#endif
