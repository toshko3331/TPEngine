#include "HeadersInclude.h"
#include <math.h>
#include <string.h>
#include <float.h>

Rasterizer::Rasterizer(Bitmap* bitmap,Bitmap* texture)
{
	m_zBuffer = new float[((bitmap->GetWidth()) * (bitmap->GetHeight()))];
	std::cout << ((bitmap->GetWidth()) * (bitmap->GetHeight())) << std::endl;
	m_bitmap = bitmap;
	m_texture = texture;
}

Rasterizer::~Rasterizer()
{
	//Freeing memory.
	delete[] m_zBuffer;
}


void Rasterizer::RasterizeTPMapMesh(Matrix4f* transformationMatrix,Object& object)
{
	/* CURRENTLY BROKEN BECAUSE FACES ARE NOT EXPORTED CORRECTLY. DO NOT USE! */ 	
	//TODO:Fix this.	
	if(transformationMatrix == NULL)
	{
		std::cout << "Matrix pointer not initialized" << std::endl;
		return;
	}
	
	std::vector<Vertex> vertecies = object.GetVertexVector();
	for(unsigned int i = 0; i < vertecies.size();i+=3)
	{
		RasterizeTriangle((object.GetVertexVector().at(object.GetFaceVector().at(i))).ApplyTransformations(*transformationMatrix),
				(object.GetVertexVector().at(object.GetFaceVector().at(i+1))).ApplyTransformations(*transformationMatrix),
				(object.GetVertexVector().at(object.GetFaceVector().at(i+2))).ApplyTransformations(*transformationMatrix));
	}
}

void Rasterizer::RasterizeObjMesh(Matrix4f* transformationMatrix,Object& object)
{
	//Clearing the zBuffer.
	for(int i = 0;i < ((m_bitmap->GetWidth()) * (m_bitmap->GetHeight()));i++)
	{
		m_zBuffer[i] = FLT_MAX;
	}
	
	if(transformationMatrix == NULL)
	{
		std::cout << "Matrix pointer not initialized." << std::endl;
		return;
	}
	std::vector<float> vertecies = object.GetRawVertexVector();
	std::vector<int> faces = object.GetFaceVector();
	std::vector<float> texels = object.GetTexelVector();
	for(unsigned int i = 0;i < faces.size();i+=6)
	{
		//TODO:This looks like total voodo to outsiders, comment it a bit.
		Vertex v1 = Vertex(
				Vector4f(vertecies.at(faces.at(i + 0) * 3 + 0),vertecies.at(faces.at(i + 0) * 3 + 1),vertecies.at(faces.at(i + 0) * 3 + 2),1),
				Vector2f(texels.at(faces.at(i + 1) * 2 + 0),texels.at(faces.at(i + 1) * 2 + 1 )));
		Vertex v2 = Vertex(
				Vector4f(vertecies.at(faces.at(i + 2) * 3 + 0),vertecies.at(faces.at(i + 2) * 3 + 1),vertecies.at(faces.at(i + 2) * 3 + 2),1),
				Vector2f(texels.at(faces.at(i + 3) * 2 + 0),texels.at(faces.at(i + 3) * 2 + 1 )));
		Vertex v3 = Vertex(
				Vector4f(vertecies.at(faces.at(i + 4) * 3 + 0),vertecies.at(faces.at(i + 4) * 3 + 1),vertecies.at(faces.at(i + 4) * 3 + 2),1),
				Vector2f(texels.at(faces.at(i + 5) * 2 + 0),texels.at(faces.at(i + 5) * 2 + 1 )));
		RasterizeTriangle(v1.ApplyTransformations(*transformationMatrix),v2.ApplyTransformations(*transformationMatrix),v3.ApplyTransformations(*transformationMatrix));
	} 
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
	float zBufferXGradient = (right.GetZBuffer() - left.GetZBuffer())/DistanceOfX;

	float UValue = left.GetUOverZ() + UValueXGradient * xApproxFloatError;
	float VValue = left.GetVOverZ() + VValueXGradient * xApproxFloatError;
	float OneOverZ = left.GetOneOverZ() + OneOverZXGradient * xApproxFloatError;
	float zBuffer = left.GetZBuffer()  + zBufferXGradient * xApproxFloatError;

	for(int currentX = xBegin;currentX < xEnd;currentX++)
	{

		int i = currentX + currentY * m_bitmap->GetWidth();
		if(zBuffer < m_zBuffer[i])
		{		
			m_zBuffer[i] = zBuffer;
			float z = 1.0f/OneOverZ;
			int textureX = (int)(((m_texture->GetWidth() - 1) + 0.5f) * (UValue * z));
			int textureY = (int)(((m_texture->GetHeight() - 1) + 0.5f) * (VValue * z));
			//The x values at whcih to draw the pixel is decided by the minimum and maximum variables
			//while the Y-Axis is decided from the function from which this function is called.
			m_bitmap->CopyTexelToPixel(textureX,textureY,currentX,currentY,m_texture);
		}

		UValue = UValue + UValueXGradient;
		VValue = VValue + VValueXGradient;
		OneOverZ = OneOverZ + OneOverZXGradient;
		zBuffer = zBuffer+ zBufferXGradient;

	}
}
