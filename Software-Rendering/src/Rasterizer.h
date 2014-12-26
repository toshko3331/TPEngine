#pragma once
#include "HeadersInclude.h"


class Rasterizer 
{
	public:
		Rasterizer(Bitmap* bitmap);
		//Error checking of the order of the Verticies being passed in should be done by the user of the function
		void RasterizeTriangle(Vertex maxYVertex,Vertex midYVertex,Vertex minYVertex);
		void ScanEdge(Edge left,Edge right,bool IsRightEdgeLongerThanLeft, bool secondTriangle);//,Vector4f handedness);
		void DrawScanLine(int min,int max,int currentY);
	private:
		Bitmap* m_bitmap;
	
};
