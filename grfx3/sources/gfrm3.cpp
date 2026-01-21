//graphics frames - P. Ahrenkiel

#include <cstdlib>

#include "mth.hpp"

#include "vtr3.hpp"
#include "pnt3.hpp"
#include "idx3.hpp"
#include "ags3.hpp"
#include "atr3.hpp"
#include "scl3.hpp"

#include "gpnt3.hpp"
#include "gfrm3.hpp"

const gfrm3 gfrm3::unitF(pnt3(-0.5,-0.5,-0.5),vtr3(1.,1.,1.));

gfrm3::gfrm3(const pnt3& coordP,const vtr3& diagV,const idx3& coordI)
{
	auto B=bas3({diagV.x(),0.,0.},{0.,diagV.y(),0.},{0.,0.,diagV.z()});
	auto coordV=B*coordI;
	auto P0=coordP-coordV;
	A()={B,P0};
}

bool gfrm3::operator==(const gfrm3 &F) const
{
	return true;//(P()==F.P())&&(B()==F.B());
}

//
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
	
//
gfrm3 gfrm3::operator/=(const double x)
{
	return *this=(*this)/x;
	}

gfrm3 gfrm3::operator+(const vtr3 &V) const
{
	return atr3(V)*(*this);
}

gfrm3 gfrm3::operator-(const vtr3 &V) const
{
	return *this+(-V);
}

gfrm3 gfrm3::operator/(const double x) const
{
	return (1./x)*(*this);
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

//scale about origin
gfrm3 operator*(const double x,const gfrm3 &F)
{
	auto p0=F.center();
	auto a=atr3(0.5*F.diag())*F;
	a.B()*=scl3(x);
	a*=atr3(p0-a*idx3(0.5,0.5,0.5));
	return a;
}

//scale about center
gfrm3 gfrm3::scale(const double x) const
{
	return x*(*this);
}

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

