#pragma once
#include "HeadersInclude.h"

class Rasterizer 
{
	public:
		Rasterizer(Bitmap* bitmap);
		//Error checking of the order of the Verticies being passed in should be done by the user of the function
		void RasterizeTriangle(Vertex maxYVertex,Vertex midYVertex,Vertex minYVertex);
		void LeftLongestEdge(Edge left,Edge right,bool secondTriangle,Vector4f color);
		void RightLongestEdge(Edge left,Edge right,bool secondTriangle,Vector4f color);
		void RasterizeHorizontalLine(Edge left,Edge right,int currentY,Vector4f color);

	private:
		Bitmap* m_bitmap;
	
};
