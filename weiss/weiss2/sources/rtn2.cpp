//2-D rotations - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss2.hpp"

using namespace std;

//
Rtn2::Rtn2(const Rtn2 &R):Trf2(R)
{
}

//
Rtn2::Rtn2(const Vtr2 &V,const Vtr2 &Vp):Trf2()
{
	double magV=V.len();
	double magVp=Vp.len();

	if((magV>0.)&&(magVp>0.))
	{
		double angle=atan2(V.dot(Vp),V.cross(Vp));
		*this=Rtn2(angle);
	}
}

//
Rtn2::Rtn2(const double angle):Trf2()
{
	double c=cos(angle),s=sin(angle);
	double u[2][2]={{c,s},{-s,c}};
	*this=Trf2(u);
}

//
Rtn2::Rtn2(const Trf2 &T)
{
	for(size_t i=0;i<2;i++)
		for(size_t j=0;j<2;j++)
			_p[i][j]=T(i,j);
}

//
Rtn2 Rtn2::operator*(const Rtn2 &R) const
{
	return Trf2(*this)*R;
}

//
Rtn2 Rtn2::operator/(const Rtn2 &R) const
{
	return Trf2(*this)/R;
}

//
Rtn2 Rtn2::operator/=(const Rtn2 &R)
{
	return (*this)*=(*this)/R;
}

//
Rtn2 Rtn2::inv() const
{
	return Trf2(*this).inv();

}
