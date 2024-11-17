//colors - P. Ahrenkiel

#include <cstdlib>
#include <math.h>
#include "col.hpp"

const colRGB colRGB::Black(0.,0.,0.);
const colRGB colRGB::White(1.,1.,1.);
const colRGB colRGB::Red(1.,0.,0.);
const colRGB colRGB::Green(0.,1.,0.);
const colRGB colRGB::Blue(0.,0.,1.);
const colRGB colRGB::Yellow(1.,1.,0.);
const colRGB colRGB::Magenta(1.,0.,1.);
const colRGB colRGB::Cyan(1.,0.,1.);

//
colRGB colRGB::operator+(const colRGB& c) const
{
	colRGB cp;
	cp._red=_red+c._red;
	cp._green=_green+c._green;
	cp._blue+=_blue+c._blue;
	return cp;
}
	
//
colRGB colRGB::operator-(const colRGB& c) const
{
	colRGB cp;
	cp._red=_red-c._red;
	cp._green=_green-c._green;
	cp._blue=_blue-c._blue;
	return cp;
}
	
//
colRGB operator*(const float x,const colRGB& c)
{
	colRGB cp;
	cp.red()=x*c.red();
	cp.green()=x*c.green();
	cp.blue()=x*c.blue();
	return cp;
}

//
colRGB colRGB::operator/(const float x) const
{
	return (1./x)*(*this);
}

//
col col::operator+(const col& c) const
{
	colRGB cpRGB = *this;
	cpRGB = cpRGB + c;
	return col(cpRGB, 0.5 * (_alpha+c._alpha));
}
	
//
col col::operator-(const col& c) const
{
	colRGB cpRGB = *this;
	cpRGB = cpRGB - c;
	return col(cpRGB, 0.5 * (_alpha+c._alpha));
}
	
//
col col::operator/(const float x) const
{
	return (1./x)*(*this);
}
	
//
col operator*(float x,const col& c)
{
	colRGB cpRGB = c;
	cpRGB = x * cpRGB;
	return col(cpRGB, c.alpha());
}
