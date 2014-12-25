#include "HeadersInclude.h"

void Rasterizer::DrawHorizontalLine(Vertex beginningVertex,Vertex endVertex,Bitmap* bitmap)
{
	for(float i = beginningVertex.GetX(); i < endVertex.GetX();i++)
	{
		bitmap->SetPixel(i,beginningVertex.GetY(),0,0,0,0);
	}
}

void Rasterizer::FillTriangle()
{
	//TODO:Implelemnt lel
}
