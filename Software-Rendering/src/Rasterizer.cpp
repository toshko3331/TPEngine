#include "HeadersInclude.h"
#include <math.h>
//Temporary includes for the test code.
#include <time.h>
//End of temporary includes.
Rasterizer::Rasterizer(Bitmap* bitmap,Bitmap* texture)
{
	m_bitmap = bitmap;
	m_texture = texture;
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
	Gradients gradients = Gradients(minYVertex,midYVertex,maxYVertex);
	Edge topToBottom = Edge(gradients,minYVertex,maxYVertex,0);
	Edge topToMiddle = Edge(gradients,minYVertex,midYVertex,0);
	Edge middleToBottom = Edge(gradients,midYVertex,maxYVertex,1);

	bool rightOrLeft = minYVertex.Normal(maxYVertex,midYVertex) >= 0;

	ScanEdges(topToBottom,topToMiddle,rightOrLeft,false,gradients);
	ScanEdges(topToBottom,middleToBottom,rightOrLeft,true,gradients);
}

void Rasterizer::ScanEdges(Edge first, Edge second, bool rightOrLeft,bool secondTriangle,Gradients gradients)
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
		RasterizeHorizontalLine(left, right, j,gradients);
		left.Step();
		right.Step();
	}
}

void Rasterizer::RasterizeHorizontalLine(Edge left,Edge right,int currentY,Gradients gradients)
{

	//These 2 variables can be thought of as limits. 
	//xBegin sets the minimum and xEnd sets the maximum values for the x axis.
	//These are the values at which a pixel should be filled
	int xBegin = ceil(left.GetX());
	int xEnd = ceil(right.GetX());
	float xApproxFloatError = xBegin - left.GetX();

	float DistanceOfX = right.GetX() - left.GetX();
	float UValueXGradient = (right.GetUOverZ() - left.GetUOverZ())/DistanceOfX;
	float VValueXGradient = (right.GetVOverZ() - left.GetVOverZ())/DistanceOfX;
	float OneOverZXGradient = (right.GetOneOverZ() - left.GetOneOverZ())/DistanceOfX;
		
	float UValue = left.GetUOverZ() + UValueXGradient * xApproxFloatError;
	float VValue = left.GetVOverZ() + VValueXGradient * xApproxFloatError;
	float OneOverZ = left.GetOneOverZ() + OneOverZXGradient * xApproxFloatError;

	for(int currentX = xBegin;currentX < xEnd;currentX++)
	{
		float z = 1.0f/OneOverZ;

		int textureX = (int)(((m_texture->GetWidth() - 1) + 0.5f) * (UValue * z));
		int textureY = (int)(((m_texture->GetHeight() - 1) + 0.5f) * (VValue * z));

		//The x values at whcih to draw the pixel is decided by the minimum and maximum variables
		//while the Y-Axis is decided from the function from which this function is called.
		m_bitmap->CopyTexelToPixel(textureX,textureY,currentX,currentY,m_texture);
		
		UValue = UValue + UValueXGradient;
		VValue = VValue + VValueXGradient;
		OneOverZ = OneOverZ + OneOverZXGradient;

	}
}
