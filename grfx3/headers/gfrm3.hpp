// 3-D graphics frames - P. Ahrenkiel

#ifndef _GFRM3_
#define _GFRM3_

#include "weiss.hpp"

class gfrm3
{
private:
	pnt3 _originP;//center
	vtr3 _diagV;

public:
	gfrm3(){}
	gfrm3(const pnt3& originP,const vtr3& diagV):_originP(originP),_diagV(diagV){}

	double left() const{return (_originP-0.5*_diagV).x();}
	double front() const{return (_originP-0.5*_diagV).y();}
	double bottom() const{return (_originP-0.5*_diagV).z();}

	double right() const{return (_originP+0.5*_diagV).x();}
	double back() const{return (_originP+0.5*_diagV).y();}
	double top() const{return (_originP+0.5*_diagV).z();}
	
	double width() const{return _diagV.x();}
	double depth() const{return _diagV.y();}
	double height() const{return _diagV.z();}

	pnt3 &origin(){return _originP;}
	pnt3 const &origin() const{return _originP;}

	vtr3 &diag(){return _diagV;}
	vtr3 const &diag() const{return _diagV;}
	
	bool operator==(const gfrm3 &f) const;
	
	gfrm3 operator+(const vtr3 &V) const;
	gfrm3 operator-(const vtr3 &V) const;
	gfrm3 operator/(const double x) const;

	gfrm3 operator+=(const vtr3 &V);
	gfrm3 operator-=(const vtr3 &V);
	gfrm3 operator*=(const double x);
	gfrm3 operator/=(const double x);
	
	gfrm3 map(const gfrm3 &newF,const gfrm3 &oldF) const;
	bool isIn(const gfrm3 &F) const;
	bool overlaps(const gfrm3 &F) const;
	friend gfrm3 operator*(const double x,const gfrm3 &f);
	//void move(vtr3 &V,const gfrm3 &boundF) const;
	bool isIn(const pnt3 &P) const;
	
	//
	pnt3 coord(const double xc,const double yc,const double zc) const;
	pnt3 center() const{return coord(0.5,0.5,0.5);}
	pnt3 corner000() const{return coord(0.,0.,0.);}
	pnt3 corner100() const{return coord(1.,0.,0.);}
	pnt3 corner010() const{return coord(0.,1.,0.);}
	pnt3 corner001() const{return coord(0.,0.,1.);}
	pnt3 corner111() const{return coord(1.,1.,1.);}
	pnt3 corner011() const{return coord(0.,1.,1.);}
	pnt3 corner101() const{return coord(1.,0.,1.);}
	pnt3 corner110() const{return coord(1.,1.,0.);}
	pnt3 faceCenter0YZ() const{return coord(0.,0.5,0.5);}
	pnt3 faceCenter1YZ() const{return coord(1.,0.5,0.5);}
	pnt3 faceCenterX0Z() const{return coord(0.5,0.,0.5);}
	pnt3 faceCenterX1Z() const{return coord(0.5,1.,0.5);}
	pnt3 faceCenterXY0() const{return coord(0.5,0.5,0.);}
	pnt3 faceCenterXY1() const{return coord(0.5,0.5,1.);}

	double meanSize() const{return _diagV.len();}
	double halfMeanSize() const{return 0.5*meanSize();}
	gfrm3 scale(const double f) const;
	void move(vtr3 &V,const gfrm3 &boundF) const;

	double awidth() const{return fabs(width());}
	double adepth() const{return fabs(depth());}
	double aheight() const{return fabs(height());}

	gfrm3 &R(){return *this;}
	const gfrm3 &R() const{return *this;}
	
	friend double width(const gfrm3 &F){return F.width();}
	friend double height(const gfrm3 &F){return F.height();}

	friend std::ostream& operator<<(std::ostream &os,const gfrm3 &F);

	static const gfrm3 unitF;
	
	operator ags3() const;
};

typedef arr::arr1<gfrm3> gfrm3_arr1;

#endif
