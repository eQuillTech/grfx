//graphics boundaries - Phil Ahrenkiel

#ifndef _GBDY_
#define _GBDY_

#ifndef _GRFX_
#include "grfx2.hpp"
#endif

//
class gbdy
{
	gply m_coarse,m_fine;
	
public:
	gbdy():m_coarse(),m_fine(){}
	gbdy(const gply& pCoarse,const gply& pFine):m_coarse(pCoarse),m_fine(pFine){}
	
	gply coarse() const{return m_coarse;}
	gply fine() const{return m_fine;}
	
	gbdy operator+(const gvtr &v) const{return gbdy(coarse()+v,fine()+v);}
	gbdy map(const gfrm  &fNew,const gfrm  &fOld);
	const gbdy map(const gfrm  &fNew,const gfrm  &fOld) const;

	friend std::ostream& operator<<(std::ostream &os,const gbdy &b);
};

typedef arr::arr1<gbdy> gbdy_arr1;
extern const gbdy nullBdy;

#endif
