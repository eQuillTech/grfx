// Mesh - P.Ahrenkiel, 2023
#include <cstdlib>
#include <math.h>

#include <queue>
#include <list>
#include <stack>

#include "Mesh.hpp"

bool Mesh::_showData(false);

//find the WFTIndex in the vector, or push it to the back if not found. Return its vector index.
std::size_t findIndexOrPushVertex(WFTIndexVector &wftIndexVector,const WFTIndex &wftIndex)
{
	bool found=false;
	std::size_t index=0;
	std::size_t nWFT=wftIndexVector.size();
	for(std::size_t i=0;i<nWFT;++i)
	{
		const WFTIndex v=wftIndexVector[i];
		if(wftIndex==v)
		{
			found=true;
			index=i;
			break;
		}
	}
	if(!found)
	{
		index=nWFT;
		wftIndexVector.push_back(wftIndex);
	}
	return index;
}

//
Mesh::Mesh()
{
	_vertex.emplace_back(pnt3(-1.,-1.,0),vtr3::Vz,pnt2(0.,1.));
	_vertex.emplace_back(pnt3(1.,-1.,0),vtr3::Vz,pnt2(1.,1.));
	_vertex.emplace_back(pnt3(1.,1.,0),vtr3::Vz,pnt2(1.,0.));
	_vertex.emplace_back(pnt3(-1.,1.,0),vtr3::Vz,pnt2(0.,0.));

	_currentSubmesh=new SubMesh();
	_submesh["empty"]=_currentSubmesh;
	_currentSubmesh->_tris.emplace_back(0,1,2);
	_currentSubmesh->_tris.emplace_back(0,2,3);
}

//
Mesh::~Mesh()
{
	clear();
}

//
void Mesh::clear()
{
	for(auto &[key, submesh]:_submesh)
		delete submesh;
	_submesh.clear();
	_vertex.clear();
	_currentSubmesh=nullptr;
}

// 
void Mesh::operator*=(const atr3 &T)
{
	for(auto &vertex:_vertex)
	{
		pnt3 &P=std::get<0>(vertex);
		P*=T;
		
		vtr3 &nV=std::get<1>(vertex);
		nV*=T.A();
	}
	_range.min()*=T;
	_range.max()*=T;
}

void Mesh::operator/=(const atr3 &T)
{
	*this*=T.inv();
}

void Mesh::FindRange()
{
	_range.init();
	for(auto &vertex:_vertex)
	{
		_range.expand(std::get<0>(vertex));
	}
}
