//
//  Tri.hpp
//  MetalTest
//
//  Created by Phil Ahrenkiel on 4/21/23.
//

#ifndef _TOPO_
#define _TOPO_

#include "Mesh.hpp"
#include "TopoTri.hpp"

//Wavefront vertex assignment
struct WFTIndex
{
	union
	{
		struct
		{
			long _iPos,_iNorm,_iTex;
		};
		long _p[3]; //array representation
	};
	WFTIndex(){}
	WFTIndex(const long iPos,const long iNorm,const long iTex):
		_iPos(iPos),_iNorm(iNorm),_iTex(iTex){}
	bool operator==(const WFTIndex &rhs) const
	{
		return ((_p[0]==rhs._p[0])&&(_p[1]==rhs._p[1])&&(_p[2]==rhs._p[2]));
	}
};

typedef std::vector<WFTIndex> WFTIndexVector;
std::size_t findIndexOrPushVertex(WFTIndexVector &wftIndexVector,const WFTIndex &wftIndex);

//
enum FragmentMode
{
	NoColorOrTexture = 0,
	UseColorOnly = 1,
	UseTextureOnly = 2,
	UseColorAndTexture = 3
};

struct FragmentInfo
{
	col _color=col::Red;
	std::string _sImage="";
	FragmentMode _fragMode=NoColorOrTexture;
	float _luminosity=0.0;
	bool _useAlphaTest=false;
};

typedef std::map<std::string,FragmentInfo> FragmentMap;
typedef std::map<std::string,CGImageRef> ImageMap;


#endif
