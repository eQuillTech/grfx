//graphics boundaries - P. Ahrenkiel

#include <cstdlib>
#include "CoreGraphics/CoreGraphics.h"

#include "tlbx.hpp"
#include "grfx2.hpp"

using namespace std;

//const gbdy nullBdy(nullPly,nullPly);

//
gbdy gbdy::map(const gfrm  &fNew,const gfrm  &fOld)
{
	return gbdy(coarse().map(fNew,fOld),fine().map(fNew,fOld));
};

//
const gbdy gbdy::map(const gfrm  &fNew,const gfrm  &fOld) const
{
	return gbdy(coarse().map(fNew,fOld),fine().map(fNew,fOld));
};

//
ostream& operator<<(ostream &os,const gbdy &b)
{
	os<<"coarse:"<<b.coarse()<<endl;
	os<<"fine:"<<b.fine()<<endl;
	return os;
}
