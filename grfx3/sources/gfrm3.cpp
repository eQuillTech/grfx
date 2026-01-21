//graphics frames - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "pnt3.hpp"
#include "ags3.hpp"

#include "gfrm3.hpp"

const gfrm3 gfrm3::unitF(pnt3(-0.5,-0.5,-0.5),vtr3(1.,1.,1.));

bool gfrm3::operator==(const gfrm3 &F) const
{
	return (_originP==F._originP)&&(_diagV==F._diagV);
}

gfrm3 gfrm3::operator+=(const vtr3 &V)
{
	return *this=*this+V;
	}

gfrm3 gfrm3::operator-=(const vtr3 &V)
{
	return *this=*this-V;
	}

gfrm3 gfrm3::operator*=(double x)
{
	return *this=x*(*this);
}

gfrm3 gfrm3::operator/=(const double x)
{
	return *this=(*this)/x;
}

gfrm3 gfrm3::operator+(const vtr3 &V) const
{
	return gfrm3(_originP+V,_diagV);
}

gfrm3 gfrm3::operator-(const vtr3 &V) const
{
	return *this+(-V);
}

gfrm3 gfrm3::operator/(const double x) const
{
	return gfrm3(pnt3::Po+(_originP-pnt3::Po)/x,_diagV/x);
}

pnt3 gfrm3::coord(const double xc,const double yc,const double zc) const
{
	return _originP-0.5*_diagV+vtr3(xc*_diagV.x(),yc*_diagV.y(),zc*_diagV.z());
}

bool gfrm3::isIn(const pnt3 &P) const
{
	double rx=(P.x()-left())/(right()-left());
	double ry=(P.y()-front())/(back()-front());
	double rz=(P.z()-bottom())/(top()-bottom());
	return (rx>=0.)&&(rx<=1.)&&(ry>=0.)&&(ry<=1.)&&(rz>=0.)&&(rz<=1.);
}

bool gfrm3::isIn(const gfrm3 &F) const
{
	return isIn(F.corner000())&&isIn(F.corner111());
}

bool gfrm3::overlaps(const gfrm3 &F) const
{
	double resX=mth::sgn(F.left()-left())
		+mth::sgn(F.left()-right())
		+mth::sgn(F.right()-left())
		+mth::sgn(F.right()-right());
		
	double resY=mth::sgn(F.front()-front())
		+mth::sgn(F.front()-back())
		+mth::sgn(F.back()-front())
		+mth::sgn(F.back()-front());

	double resZ=mth::sgn(F.bottom()-bottom())
		+mth::sgn(F.bottom()-top())
		+mth::sgn(F.top()-bottom())
		+mth::sgn(F.top()-top());

	return (fabs(resX)<3.)&&(fabs(resY)<3.)&&(fabs(resZ)<3.);
}

//scale about center
gfrm3 gfrm3::scale(const double x) const
{
	vtr3 diagV=x*_diagV;
	return gfrm3(_originP,diagV);
}

//
void gfrm3::move(vtr3 &V,const gfrm3 &boundF) const
{
	double fac=1.;
	if(V.x()!=0.)
	{
		double fLeft=(boundF.left()-left())/V.x();
		double fRight=(boundF.right()-right())/V.x();
		if((fLeft>0.)&&(fLeft<fac))fac=fLeft;
		if((fRight>0.)&&(fRight<fac))fac=fRight;
	}
	if(V.y()!=0.)
	{
		double fTop=(boundF.back()-front())/V.y();
		double fBottom=(boundF.front()-front())/V.y();
		if((fTop>0.)&&(fTop<fac))fac=fTop;
		if((fBottom>0.)&&(fBottom<fac))fac=fBottom;
		
	}
	if(V.z()!=0.)
	{
		double fTop=(boundF.top()-top())/V.z();
		double fBottom=(boundF.bottom()-bottom())/V.z();
		if((fTop>0.)&&(fTop<fac))fac=fTop;
		if((fBottom>0.)&&(fBottom<fac))fac=fBottom;
		
	}
	V*=fac;
}

gfrm3 gfrm3::map(const gfrm3 &newF,const gfrm3 &oldF) const
{
	gfrm3 rp=*this;
	rp._originP=gpnt3(_originP).map(newF,oldF);
	rp._diagV=gpnt3(_originP+_diagV).map(newF,oldF)-rp._originP;
	return rp;
}

//scale about origin
gfrm3 operator*(const double x,const gfrm3 &F)
{
	return gfrm3(pnt3::Po+x*(F._originP-pnt3::Po),x*F._diagV);
}

std::ostream& operator<<(std::ostream &os,const gfrm3 &F)
{
	os<<"["<<F._originP<<","<<F._diagV<<"]";
	return os;
}

gfrm3::operator ags3() const
{
	return ags3(bas3(_diagV.x()*vtr3::Vx,_diagV.y()*vtr3::Vy,_diagV.z()*vtr3::Vz),_originP);
}
