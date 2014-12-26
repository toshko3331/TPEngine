#include "HeadersInclude.h"
#include <math.h>
Rasterizer::Rasterizer(Bitmap* bitmap)
{
	m_bitmap = bitmap;
}

void Rasterizer::RasterizeTriangle(Vertex minYVertex,Vertex midYVertex,Vertex maxYVertex)
{
	 //Sort the vertices
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
	///Major Debug Code///
	std::cout << "(" << minYVertex.GetX() << "," << minYVertex.GetY() << ")" <<std::endl;
	std::cout << "(" << midYVertex.GetX() << "," << midYVertex.GetY() << ")" <<std::endl;
	std::cout << "(" << maxYVertex.GetX() << "," << maxYVertex.GetY() << ")" <<std::endl;
	///End Debug Code////
	Edge topToBottom = Edge(minYVertex,maxYVertex);
	Edge topToMiddle = Edge(minYVertex,midYVertex);
	Edge middleToBottom = Edge(midYVertex,maxYVertex);
	///Major Debug Code///
//	std::cout << topToMiddle.GetX() << "," << topToMiddle.GetYEnd() <<std::endl;
	std::cout << topToBottom.GetYStart() << "," << topToBottom.GetYEnd() <<std::endl;
//	std::cout << middleToBottom.GetX() << "," << middleToBottom.GetYEnd() <<std::endl;
	///End Debug Code////
	//Add handedness.	
	ScanEdge(topToBottom,topToMiddle,true,false);//,minYVertex * maxYVertex);
	ScanEdge(topToBottom,middleToBottom,true,true);//,midYVertex * maxYVertex);
			
}

void Rasterizer::ScanEdge(Edge left,Edge right,bool IsRightEdgeLongerThanLeft,bool secondTriangle)//,Vector4f handedness)
{
	//TODO: make sure that the edges are in the correct order.
		
	if(IsRightEdgeLongerThanLeft)
	{
		Edge temp = left;
		left = right;
		right = temp;
	}
	
	int yBegin = left.GetYStart();
//	std::cout << yBegin << "\t" << yEnd << std::endl;
//	int yBegin = 0;
        int yEnd = left.GetYEnd();
//	std::cout << left.GetX() <<  std::endl;
//	std::cout << right.GetX() << std::endl;
//	std::cout << "//////" <<std::endl;
	std::cout << left.GetReciprocalSlope() << "\t" << right.GetReciprocalSlope() << std::endl;
	if(secondTriangle){
	for(int i = right.GetYStart();i <= yBegin;i++)
	{
		right.Step();
		
		std::cout << "Am I even here?" << std::endl;
	}
	}
	for(int currentY = yBegin;currentY <= yEnd;currentY++)
	{
		DrawScanLine(left.GetX(),right.GetX(),currentY);	
		left.Step();
		right.Step();
	}
	
//	std::cout << "Right.x after loop " << right.GetX() << std::endl;
}

void Rasterizer::DrawScanLine(int min,int max,int currentY)
{
	/*
	int xBegin = ceil(left.GetX());
	int xEnd = ceil(right.GetX());
	*/

	int xBegin = min;
	int xEnd = max;

	//std::cout << xBegin << "\t" << xEnd << std::endl;	
	for(int currentX = xBegin;currentX <= xEnd;currentX++)
	{
		m_bitmap->SetPixel(currentX,currentY,0,0,0,0);
	}
}



