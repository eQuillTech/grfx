//
//  Triangulation.hpp
//  TiffTri
//
//  Created by Phil Ahrenkiel on 4/5/23.
//

#ifndef _TOPOTRI_
#define _TOPOTRI_

#include <cstdlib>

#include "Mesh.hpp"

//
class TopoTri:public Mesh
{
public:
	TopoTri():Mesh(){}
	TopoTri
	(
		std::vector<float> &data_img,  // array of image data
		std::size_t width, std::size_t height,  // Image dimensions
		bool omit_noData,
		float noDataVal,
		float tri_res, // Resolution factor (0 - 1) for triangulation
		bool simplify_border // Specifies whether to eliminate border apices
	);

	static float CalculateRes(int sliderVal, std::size_t n_pix);

};

#endif
