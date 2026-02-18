//graphics cameras - P. Ahrenkiel

#include <cstdlib>

#include "gcmr.hpp"

gcmr::gcmr(const gfrm &F,const gpnt &aperP,double aperZ,double plateZ):
	gfrm (F),m_aperP(aperP),m_aperZ(aperZ),m_plateZ(plateZ){}

gpnt &gcmr::aperture(){return m_aperP;}
const gpnt &gcmr::aperture() const{return m_aperP;}

gfrm gcmr::plate() const{return R()+(m_aperP-pnt2::origin);}
