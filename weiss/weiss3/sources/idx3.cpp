//indices - P. Ahrenkiel
#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss3.hpp"

const idx3 idx3::I000(0.,0.,0.);
const idx3 idx3::I100(1.,0.,0.);
const idx3 idx3::I010(0.,1.,0.);
const idx3 idx3::I001(0.,0.,1.);
const idx3 idx3::I111(1.,1.,1.);

//
std::ostream& operator<<(std::ostream &os,const idx3 &I)
{
	os<<"("<<I.h()<<","<<I.k()<<","<<I.l()<<")";
	return os;
}

//
idx3 idx3::round() const
{
	idx3 I;
	for(size_t i=0;i<3;++i)
		I._p[i]=mth::roundoff(_p[i]);
	return I;
}

/*
Axs3 idx3::operator*(const vtr3 &V) const
{
	return Axs3(_x*V,_y*V,_z*V,pnt3::Po);
}
*/
//
idx3 round(const idx3 &I){return I.round();}
