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
//	transformations.PrintToConsole();
	minYVertex = minYVertex.ApplyTransformations(transformations).PerspectiveDivide();
	midYVertex = midYVertex.ApplyTransformations(transformations).PerspectiveDivide(); 
	maxYVertex = maxYVertex.ApplyTransformations(transformations).PerspectiveDivide(); 
	minYVertex.PrintToConsole(true);
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
	//Test code for funzies. :P
//	Vector4f color = Vector4f(rand()%255,rand()%255,rand()%255,rand()%255);
	Vector4f color = Vector4f(0,0,0,0);
	//End of test code.
	//Check weather the longest side is on the right or left.
	//This determines the function it is going to use to draw the specific triangle. 
	if(topToBottom.GetX() < middleToBottom.GetX())
	{
		//This function call is for drawing the top triangle.
		LeftLongestEdge(topToBottom,topToMiddle,false,color);
		//This function call is for drawing the bottom part of the triangle.
		LeftLongestEdge(topToBottom,middleToBottom,true,color);
	}
	else
	{
		//This function call is for drawing the top triangle.
		RightLongestEdge(topToMiddle,topToBottom,false,color);
		//This function call is for drawing the bottom part of the triangle.
		RightLongestEdge(middleToBottom,topToBottom,true,color);
	}
}

void Rasterizer::RightLongestEdge(Edge left,Edge right,bool secondTriangle,Vector4f color)
{	
	//yBegin = The point on the Y-Axis at which we are going to start drawing the triangle.
	int yBegin = right.GetYStart();
	//yEnd = The point on the Y-Axis at which we are going to stop drawing the triangle.
	int yEnd = left.GetYEnd();
	
	//The algorithm is based on drawing the bottom and top triangles sepratly.
	//It is necessary to do a few things different if it is drawing the bottom half of the triangle.
	if(secondTriangle){
		//Set the beginning of the y-axis to the appropriate value.
		//This is done by simply getting the midYVertex's Y positon since that is the beginning
		//of the bottom part of the triangle.
		yBegin = left.GetYStart();
		//Setting the proper y-axis end of the 2nd triangle.
		yEnd = right.GetYEnd();
		//Making sure that the x value of the longest side is stepped so it is
		//at the position that starts the bottom part of the triangle.
		for(int i = right.GetYStart();i < left.GetYStart();i++)
		{
			right.Step();	
		}
	}
	
	for(int currentY = yBegin;currentY < yEnd;currentY++)
	{
		RasterizeHorizontalLine(left,right,currentY,color);	
		left.Step();
		right.Step();
	}	
}

void Rasterizer::LeftLongestEdge(Edge left,Edge right,bool secondTriangle,Vector4f color)
{
	
	/*									*
	 *	REFFER TO ABOVE FUNCTION FOR COMMENTS AND BRIEF EXPLANATIONS	*
	 *									*/

	int yBegin = left.GetYStart();
	int yEnd = right.GetYEnd();
	
	if(secondTriangle)
	{
		yBegin = right.GetYStart();
		yEnd = left.GetYEnd();
		
		for(int i = left.GetYStart();i < right.GetYStart();i++)
		{
			left.Step();
		}
	}
	for(int currentY = yBegin;currentY < yEnd;currentY++)
	{
		RasterizeHorizontalLine(left,right,currentY,color);	
		//Increment our values so we can step along the edge.
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
