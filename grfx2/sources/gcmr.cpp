//graphics cameras - P. Ahrenkiel

#include <cstdlib>

#include "gcmr.hpp"

gcmr::gcmr(const gfrm  &F,const gpnt &aperP=pnt2::Po,double aperZ=-100.,double plateZ=0.):
	gfrm (F),m_aperP(aperP),m_aperZ(aperZ),m_plateZ(plateZ){}

gpnt &gcmr::aperture(){return m_aperP;}
const gpnt &aperture() const{return m_aperP;}

gfrm gcmr::plate() const{return R()+(m_aperP-pnt2::Po);}
