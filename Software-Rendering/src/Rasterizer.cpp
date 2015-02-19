#include "HeadersInclude.h"
#include <string.h>
#include <float.h>

Rasterizer::Rasterizer(Bitmap* bitmap,Textures& textures,OBJLevel& level) : m_textures(textures),m_level(level)
{
	m_zBuffer = new float[((bitmap->GetWidth()) * (bitmap->GetHeight()))];
	m_bitmap = bitmap;
	m_texture = NULL;
	this->ClearZBuffer();
}

Rasterizer::~Rasterizer()
{
	//Freeing memory.
	delete[] m_zBuffer;
}

void Rasterizer::ClearZBuffer()
{
	//Clearing the zBuffer.
	for(int i = 0;i < m_bitmap->GetWidth() * m_bitmap->GetHeight();i++)
	{
		m_zBuffer[i] = FLT_MAX;
	}
}

bool Rasterizer::ClipAxis(std::vector<Vertex>& vertices,std::vector<Vertex>& help,int index)
{
	ClipPart(vertices,index,1, help);
	vertices.clear();
	
	if(help.empty())
	{
		return false;
	}

	ClipPart(help,index,-1,vertices);
	help.clear();
	
	return !vertices.empty();
}

void Rasterizer::ClipPart(std::vector<Vertex>& vertices, int index, float CF, std::vector<Vertex>& finalV)
{
	Vertex beforeVertex = vertices.at(vertices.size() - 1);
	float beforePart = beforeVertex.GetBasedOnIndex(index) * CF;
	bool beforeInside = beforePart <= beforeVertex.GetW();
	
	for(unsigned int i = 0;i < vertices.size();i++)
	{
		Vertex nowVertex = vertices.at(i);
		float nowPart = nowVertex.GetBasedOnIndex(index) * CF;
		bool nowInside = nowPart <= nowVertex.GetW();

		if(nowInside ^ beforeInside)
		{
			float lerpAmount = (beforeVertex.GetW() - beforePart) / ((beforeVertex.GetW() - beforePart) - (nowVertex.GetW() - nowPart));

			finalV.push_back(beforeVertex.Lerp(nowVertex,lerpAmount));
		}	
	
		if(nowInside)
		{
			finalV.push_back(nowVertex);
		}

		beforeVertex = nowVertex;
		beforePart = nowPart;
		beforeInside = nowInside;
	}
}

void Rasterizer::RasterizeObjMesh(Matrix4f transformationMatrix,Object* object)
{
	//TODO: When textures can be read from files auto determine them by calling "object.GetTextureName()".
	m_texture = m_textures.GetTextureByName("res/64x64.png");
	
	if(m_texture == NULL)
	{
		ErrorReport::WriteToLog("Texture could not be assinged correctly in rasterizer.");
	}
	
	std::vector<float> raw_vertices = m_level.GetVertecies();
	std::vector<int> faces = object->GetFaceVector();
	std::vector<float> texels = m_level.GetTexelVector();

	//transformationMatrix = transformationMatrix.Translate(Vector3f(4,0,0));
	for(unsigned int i = 0;i < faces.size();i+=9)
	{
		//TODO:This looks like total voodo to outsiders, comment it a bit.
		Vertex v1 = Vertex(
				Vector4f(raw_vertices.at(faces.at(i + 0) * 3 + 0),raw_vertices.at(faces.at(i + 0) * 3 + 1),raw_vertices.at(faces.at(i + 0) * 3 + 2),1),
				Vector2f(texels.at(faces.at(i + 1) * 2 + 0),texels.at(faces.at(i + 1) * 2 + 1 ))).ApplyTransformations(transformationMatrix);
		Vertex v2 = Vertex(
				Vector4f(raw_vertices.at(faces.at(i + 3) * 3 + 0),raw_vertices.at(faces.at(i + 3) * 3 + 1),raw_vertices.at(faces.at(i + 3) * 3 + 2),1),
				Vector2f(texels.at(faces.at(i + 4) * 2 + 0),texels.at(faces.at(i + 4) * 2 + 1 ))).ApplyTransformations(transformationMatrix);
		Vertex v3 = Vertex(
				Vector4f(raw_vertices.at(faces.at(i + 6) * 3 + 0),raw_vertices.at(faces.at(i + 6) * 3 + 1),raw_vertices.at(faces.at(i + 6) * 3 + 2),1),
				Vector2f(texels.at(faces.at(i + 7) * 2 + 0),texels.at(faces.at(i + 7) * 2 + 1 ))).ApplyTransformations(transformationMatrix);
		
		bool v1IsInsideScreen = v1.IsInsideScreen();
		bool v2IsInsideScreen = v2.IsInsideScreen();
		bool v3IsInsideScreen = v3.IsInsideScreen();

		//If all the vertices are inside the screen than draw the triangle.
		if(v1IsInsideScreen && v2IsInsideScreen && v3IsInsideScreen)
		{
			RasterizeTriangle(v1,v2,v3);
		}
		
		//TODO:Fix this, not sure why it's not working, probably a problem with the IsInsideScreen function returning funky values.
		/*if(!v1IsInsideScreen && !v2IsInsideScreen && !v3IsInsideScreen)
		{
			std::cout << "And here? " << std::endl;
			return;
		}
		*/
		std::vector<Vertex> vertices;
		std::vector<Vertex> helper;
		
		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);

		if(ClipAxis(vertices,helper,0) && ClipAxis(vertices,helper,1) && ClipAxis(vertices,helper,2))
		{
			Vertex firstVertex = vertices.at(0);
			for(unsigned int i = 1;i < vertices.size() - 1;i++)
			{
				RasterizeTriangle(firstVertex,vertices.at(i),vertices.at(i+1));
			}
		}
	
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
