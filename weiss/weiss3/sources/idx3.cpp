//indices - P. Ahrenkiel
#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss3.hpp"

const Idx3 Idx3::I000(0.,0.,0.);
const Idx3 Idx3::I100(1.,0.,0.);
const Idx3 Idx3::I010(0.,1.,0.);
const Idx3 Idx3::I001(0.,0.,1.);
const Idx3 Idx3::I111(1.,1.,1.);

//
std::ostream& operator<<(std::ostream &os,const Idx3 &I)
{
	os<<"("<<I.h()<<","<<I.k()<<","<<I.l()<<")";
	return os;
}

//
Idx3 Idx3::round() const
{
	Idx3 I;
	for(size_t i=0;i<3;++i)
		I._p[i]=mth::roundoff(_p[i]);
	return I;
}

/*
Axs3 Idx3::operator*(const Vtr3 &V) const
{
	return Axs3(_x*V,_y*V,_z*V,Pnt3::Po);
}
*/
//
Idx3 round(const Idx &I){return I.round();}
