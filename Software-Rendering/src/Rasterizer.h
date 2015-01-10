#pragma once
#include "HeadersInclude.h"

class Rasterizer 
{
	public:
		Rasterizer(Bitmap* bitmap);
		//Error checking of the order of the Verticies being passed in should be done by the user of the function
		void RasterizeTriangle(Vertex maxYVertex,Vertex midYVertex,Vertex minYVertex);
		void ScanEdges(Edge a, Edge b, bool handedness,bool secondTriangle);
		void RasterizeHorizontalLine(Edge left,Edge right,int currentY,Vector4f color);

	private:
		Bitmap* m_bitmap;
	
};
