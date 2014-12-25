#pragma once
#include "HeadersInclude.h"


class Rasterizer 
{
	public:
		//Rasterizer();
		//Error checking of the order of the Verticies being passed in should be done by the user of the function
		void DrawHorizontalLine(Vertex beginningVertex,Vertex endVertex,Bitmap* bitmap);
		void FillTriangle();
};
