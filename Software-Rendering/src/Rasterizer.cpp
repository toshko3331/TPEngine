#include "HeadersInclude.h"
#include <math.h>
//Temporary includes for the test code.
#include <time.h>
//End of temporary includes.
Rasterizer::Rasterizer(Bitmap* bitmap)
{
	m_bitmap = bitmap;
	//Seeding the RNG for the test code.
	srand(time(NULL));
	//End of test code.
}

void Rasterizer::RasterizeTriangle(Vertex minYVertex,Vertex midYVertex,Vertex maxYVertex)
{

	Matrix4f transformations = Matrix4f().InitializeIdentity().WorldSpaceToScreenSpace((m_bitmap->GetWidth())/2,(m_bitmap->GetHeight())/2);	
	
	minYVertex = minYVertex.ApplyTransformations(transformations).PerspectiveDivide();
	midYVertex = midYVertex.ApplyTransformations(transformations).PerspectiveDivide(); 
	maxYVertex = maxYVertex.ApplyTransformations(transformations).PerspectiveDivide(); 
	//Sorting the vertices.
	 if(minYVertex.GetY() > midYVertex.GetY())
	 {
		Vertex temp = minYVertex;
	 	minYVertex = midYVertex;
	 	midYVertex = temp;
	 }

	 if(midYVertex.GetY() > maxYVertex.GetY())
	 {
 		Vertex temp = maxYVertex;
	 	maxYVertex = midYVertex;
	 	midYVertex = temp;
	 }

	 if(minYVertex.GetY() > midYVertex.GetY())
	 {
		Vertex temp = minYVertex; 
		minYVertex = midYVertex;
	 	midYVertex = temp;
	 }
	//Creating the edges on which the triangle will be based upon.	
	Edge topToBottom = Edge(minYVertex,maxYVertex);
	Edge topToMiddle = Edge(minYVertex,midYVertex);
	Edge middleToBottom = Edge(midYVertex,maxYVertex);

	bool rightOrLeft = minYVertex.Normal(maxYVertex,midYVertex) >= 0;

	ScanEdges(topToBottom,topToMiddle,rightOrLeft,false);
	ScanEdges(topToBottom,middleToBottom,rightOrLeft,true);
}


void Rasterizer::ScanEdges(Edge first, Edge second, bool rightOrLeft,bool secondTriangle)
{
	Edge left = first;
	Edge right = second;
	if(rightOrLeft)
	{
		if(secondTriangle)
		{
			for(int i = left.GetYStart();i < right.GetYStart();i++)
			{
				left.Step();
			}
		}
		Edge temp = left;
		left = right;
		right = temp;
	}

	if(secondTriangle && !rightOrLeft)
	{
		for(int i = left.GetYStart();i < right.GetYStart();i++)
		{
			left.Step();
		}
	}
	
	
	int yStart = second.GetYStart();
	int yEnd   = second.GetYEnd();

	for(int j = yStart; j < yEnd; j++)
	{
		RasterizeHorizontalLine(left, right, j, Vector4f(0,0,0,0));
		left.Step();
		right.Step();
	}
}

void Rasterizer::RasterizeHorizontalLine(Edge left,Edge right,int currentY,Vector4f color)
{

	//These 2 variables can be thought of as limits. 
	//xBegin sets the minimum and xEnd sets the maximum values for the x axis.
	//These are the values at which a pixel should be filled
	int xBegin = ceil(left.GetX());
	int xEnd = ceil(right.GetX());
	
	for(int currentX = xBegin;currentX < xEnd;currentX++)
	{
		//The x values at whcih to draw the pixel is decided by the minimum and maximum variables
		//while the Y-Axis is decided from the function from which this function is called.
		m_bitmap->SetPixel(currentX,currentY,color.GetX(),color.GetY(),color.GetZ(),color.GetW());
	}
}
