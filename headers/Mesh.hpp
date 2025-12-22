//  Mesh.h
//  Created by Phil Ahrenkiel on 4/7/23.
//

#ifndef _MESH_
#define _MESH_

#include <queue>
#include <list>
#include <stack>
#include <map>

#include "weiss.hpp"
#include "gfrm3.hpp"

typedef std::tuple<pnt3,vtr3,pnt2> MeshVertex;//Coord,Normal,TexCoord
typedef std::vector<MeshVertex> MeshVertexVector;

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
struct TriIndex
{
	union
	{
		struct
		{
			long _i,_j,_k;
		};
		long _p[3]; //array representation
	};
	TriIndex(){}
	TriIndex(const long i,const long j,const long k):_i(i),_j(j),_k(k){}
	TriIndex(const size_t index[3]):_i(index[0]),_j(index[1]),_k(index[2]){}
	bool operator==(const TriIndex &rhs) const
	{
		return ((_p[0]==rhs._p[0])&&(_p[1]==rhs._p[1])&&(_p[2]==rhs._p[2]));
	}
};

//
struct MeshRange
{
	pnt3 _min;
	pnt3 _max;
	
	MeshRange(){init();}
	
	void init(){_min=pnt3(1.e12,1.e12,1.e12);_max=pnt3(-1.e12,-1.e12,-1.e12);}

	pnt3 &min(){return _min;}
	pnt3 const &min() const{return _min;}

	pnt3 &max(){return _max;}
	pnt3 const &max() const{return _max;}

	double &min(const uint32_t i){return _min(i);}
	double const &min(const uint32_t i) const{return _min(i);}

	double &max(const uint32_t i){return _max(i);}
	double const &max(const uint32_t i) const{return _max(i);}

	vtr3 diag() const{return _max-_min;}
	pnt3 center() const{return _min+0.5*diag();}

	operator gfrm3() const{return gfrm3(center(),diag());}
	double const extent(const uint32_t i) const{return _max(i)-_min(i);}

	void expand(const pnt3 &P)
	{
		for(uint32_t i=0;i<3;++i)
		{
			if(P(i)<_min(i))
			{
				_min(i)=P(i);
			}
			if(P(i)>_max(i))
			{
				_max(i)=P(i);
			}
		}
	}
};

//
typedef std::vector<TriIndex> TriIndexVector;

//
struct SubMesh
{
public:
 	TriIndexVector _tris;	
	atr _T=atr::Ato;
	
	std::size_t numTriang() const{return _tris.size();}
	
	void operator*=(const atr3 &T){_T*=T;}
	void operator/=(const atr3 &T){_T/=T;}
};

//
struct Mesh
{
public:
	MeshVertexVector _vertex;
	MeshRange _range;

	std::map<std::string,SubMesh*> _submesh;
	SubMesh* _currentSubmesh;

	Mesh();
	~Mesh();
	void clear();

	std::size_t numVertex() const{return _vertex.size();}
	
	void operator*=(const trf3 &T){operator*=(atr3(T));}
	void operator*=(const atr3 &T);
	
	void operator/=(const trf3 &T){operator/=(atr3(T));}
	void operator/=(const atr3 &T);
	
	static bool _showData;
	void FindRange();
	pnt3 center(){return _range.min()+0.5*(_range.max()-_range.min());}
	double size(std::size_t iDim){return _range.max()(iDim)-_range.min()(iDim);}
};

#endif
