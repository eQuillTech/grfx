//graphics boundaries - Phil Ahrenkiel

#ifndef _GBDY_
#define _GBDY_

#ifndef _GRFX_
#include "grfx.hpp"
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
	gbdy map(const Gfrm &fNew,const Gfrm &fOld);
	const gbdy map(const Gfrm &fNew,const Gfrm &fOld) const;

	friend std::ostream& operator<<(std::ostream &os,const gbdy &b);
};

typedef arr1<gbdy> gbdy_arr1;
extern const gbdy nullBdy;

#endif
