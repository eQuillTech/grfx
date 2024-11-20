//graphics cameras - P. Ahrenkiel

#ifndef _CMR_
#define _CMR_

//#import <UIKit/UIKit.h>
#include "CoreGraphics/CoreGraphics.h"

#ifndef _GLNE_
#include <glne.hpp>
#endif

#ifndef _GPNT_
#include <gpnt.hpp>
#endif

#ifndef _GRCT_
#include <grct.hpp>
#endif

//frame is the unshifted plate
class gcmr:public gfrm 
{
protected:
	gpnt m_aperP=pnt2::Po;//aperture coords
	double m_aperZ=-100.;//aperture z
	double m_plateZ=0.;//plate z
	
public:
	gcmr(const gfrm  &F,const gpnt &aperP=pnt2::Po,double aperZ=-100.,double plateZ=0.):
		gfrm (F),m_aperP(aperP),m_aperZ(aperZ),m_plateZ(plateZ){}

	gpnt &aperture(){return m_aperP;}
	const gpnt &aperture() const{return m_aperP;}
	
	gfrm  plate() const{return R()+(m_aperP-pnt2::Po);}

	friend gfrm  gfrm ::proj(const gcmr &cmr,const double z) const;
	friend gpnt gpnt::proj(const gcmr &cmr,const double z) const;

	friend gfrm  gfrm ::invproj(const gcmr &cmr,const double z) const;
	friend gpnt gpnt::invproj(const gcmr &cmr,const double z) const;
};

#endif
