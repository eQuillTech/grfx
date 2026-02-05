//graphics cameras - P. Ahrenkiel

#ifndef _GCMR_
#define _GCMR_

#include "CoreGraphics/CoreGraphics.h"

#include "gfrm.hpp"
#include "gpnt.hpp"

class grct;

//frame is the unshifted plate
class gcmr:public gfrm 
{
protected:
	gpnt m_aperP;//aperture coords
	double m_aperZ;//aperture z
	double m_plateZ;//plate z
	
public:
	gcmr(const gfrm  &F,const gpnt &aperP=pnt2::origin,double aperZ=-100.,double plateZ=0.);

	gpnt &aperture();
	const gpnt &aperture() const;
	
	gfrm plate() const;

	friend gfrm  gfrm ::proj(const gcmr &cmr,const double z) const;
	friend gpnt gpnt::proj(const gcmr &cmr,const double z) const;

	friend gfrm  gfrm ::invproj(const gcmr &cmr,const double z) const;
	friend gpnt gpnt::invproj(const gcmr &cmr,const double z) const;
};

#endif
