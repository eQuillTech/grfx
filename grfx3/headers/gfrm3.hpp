// 3-D graphics frames - P. Ahrenkiel

#ifndef _GFRM3_
#define _GFRM3_

#include "vtr3.hpp"
#include "idx3.hpp"
#include "pnt3.hpp"
#include "ags3.hpp"

class gfrm3:private ags3
{
private:
	gfrm3(const ags3& A):ags3(A){}
	
public:
	gfrm3(){}
	gfrm3(const pnt3& coordP,const vtr3& diagV,const idx3& coordI=idx3::Imid);

	double left() const{return ((*this)*idx3::I000).x();}
	double bottom() const{return ((*this)*idx3::I000).y();}
	double front() const{return ((*this)*idx3::I000).z();}

	double right() const{return ((*this)*idx3::I111).x();}
	double top() const{return ((*this)*idx3::I111).y();}
	double back() const{return ((*this)*idx3::I111).z();}
	
	double width() const{return B().a()*vtr3::X;}
	double height() const{return B().b()*vtr3::Y;}
	double depth() const{return B().c()*vtr3::Z;}

	pnt3& origin(){return p();}
	const pnt3& origin() const{return p();}

	vtr3 diag() const{return B()*idx3::I111;}
	
	bool operator==(const gfrm3 &f) const;
	
	gfrm3 operator+(const vtr3 &V) const;
	gfrm3 operator-(const vtr3 &V) const;
	gfrm3 operator/(const double x) const;

	gfrm3 operator+=(const vtr3 &V);
	gfrm3 operator-=(const vtr3 &V);
	gfrm3 operator*=(const double x);
	gfrm3 operator/=(const double x);
	//gfrm  set(const gfrm  &r);
	
	gfrm3 map(const gfrm3 &newF,const gfrm3 &oldF) const;
	bool isIn(const gfrm3 &F) const;
	bool overlaps(const gfrm3 &F) const;
	friend gfrm3 operator*(const double x,const gfrm3 &f);
	//void move(vtr3 &V,const gfrm3 &boundF) const;
	//bool isIn(const pnt3 &P) const;
	using ags3::isIn;
	using ags3::A;
	using ags3::operator*;
	
	pnt3 coord(const double xc,const double yc,const double zc) const{return (*this)*idx3(xc,yc,zc);}
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

	double meanSize() const{return (B()*idx3::I111).len();}
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

	//friend std::ostream& operator<<(std::ostream &os,const gfrm3 &F);

	static const gfrm3 unitF;
};

typedef arr::arr1<gfrm3> gfrm3_arr1;

#endif
