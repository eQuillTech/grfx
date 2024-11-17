//graphics cameras - P. Ahrenkiel

#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <CoreGraphics/CoreGraphics.h>

#include "tlbx.hpp"
#include "grfx.hpp"

//friend
Gfrm Gfrm::proj(const gcmr &cmr,const double z) const
{
	if(z==cmr.m_aperZ)
		return 0.*unitF;
	double mag=(z-cmr.m_aperZ)/(cmr.m_plateZ-cmr.m_aperZ);
	gvtr dV=cmr.m_aperP-pnt2::Po;
	return mag*(*this-dV)+dV;
}

//friend
gpnt gpnt::proj(const gcmr &cmr,const double z) const
{
	if(z==cmr.m_aperZ)
		return pnt2::Po;
	double mag=(cmr.m_plateZ-cmr.m_aperZ)/(z-cmr.m_aperZ);
	return mag*(*this-cmr.m_aperP)+(cmr.m_aperP-pnt2::Po);
}

//friend
Gfrm Gfrm::invproj(const gcmr &cmr,const double z) const
{
	if(z==cmr.m_aperZ)
		return 0.*unitF;
	double mag=(z-cmr.m_aperZ)/(cmr.m_plateZ-cmr.m_aperZ);
	return (*this-(cmr.m_aperP-pnt2::Po))/mag+(cmr.m_aperP-pnt2::Po);
}

//friend
gpnt gpnt::invproj(const gcmr &cmr,const double z) const
{
	if(z==cmr.m_aperZ)
		return pnt2::Po;
	double mag=(cmr.m_plateZ-cmr.m_aperZ)/(z-cmr.m_aperZ);
	return mag*(*this-cmr.m_aperP)+(cmr.m_aperP-pnt2::Po);
}
