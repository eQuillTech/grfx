//graphics vectors - P. Ahrenkiel

#include <cstdlib>
#include <math.h>
#include "CoreGraphics/CoreGraphics.h"

#include "tlbx.hpp"
#include "arr.hpp"
#include "grfx.hpp"

using namespace std;

gvtr 
	zeroV(0.,0.),
	xV(1.,0.),
	yV(0.,1.);

//
ostream& operator<<(ostream &os,const gvtr &v)
{
	os<<"("<<v.x()<<","<<v.y()<<")";
	return os;
}

double dot(const gvtr &v1,const gvtr &v2){return v1.dot(v2);}
double len(const gvtr &v){return v.len();}
gvtr norm(const gvtr &v){return v.norm();}

