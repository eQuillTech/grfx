//2-D rotations - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss2.hpp"

using namespace std;

//
rtn2::rtn2(const rtn2 &R):trf2(R)
{
}

//
rtn2::rtn2(const vtr2 &V,const vtr2 &Vp):trf2()
{
	double magV=V.len();
	double magVp=Vp.len();

	if((magV>0.)&&(magVp>0.))
	{
		double angle=atan2(V.dot(Vp),V.cross(Vp));
		*this=rtn2(angle);
	}
}

//
rtn2::rtn2(const double angle):trf2()
{
	double c=cos(angle),s=sin(angle);
	double u[2][2]={{c,s},{-s,c}};
	*this=trf2(u);
}

//
rtn2::rtn2(const trf2 &T)
{
	for(size_t i=0;i<2;i++)
		for(size_t j=0;j<2;j++)
			_p[i][j]=T(i,j);
}

//
rtn2 rtn2::operator*(const rtn2 &R) const
{
	return trf2(*this)*R;
}

//
rtn2 rtn2::operator/(const rtn2 &R) const
{
	return trf2(*this)/R;
}

//
rtn2 rtn2::operator/=(const rtn2 &R)
{
	return (*this)*=(*this)/R;
}

//
rtn2 rtn2::inv() const
{
	return trf2(*this).inv();

}
