#pragma once
#include "HeadersInclude.h"

class Rasterizer 
{
	public:
		Rasterizer(Bitmap* bitmap,Textures& textures,OBJLevel& level);
		~Rasterizer();
		//Error checking of the order of the Verticies being passed in should be done by the user of the function
		void RasterizeTriangle(Vertex maxYVertex,Vertex midYVertex,Vertex minYVertex);
		void ScanEdges(Edge a, Edge b, bool handedness,bool secondTriangle,Gradients gradients);
		void RasterizeHorizontalLine(Edge left,Edge right,int currentY,Gradients gradients);
		void RasterizeObjMesh(Matrix4f transformationMatrix,Object* object);
		void ClearZBuffer();
	private:
		Bitmap* m_bitmap;
		Bitmap* m_texture;
		Textures& m_textures;
		OBJLevel& m_level;
		float* m_zBuffer;
		bool ClipAxis(std::vector<Vertex>& vertecies,std::vector<Vertex>& help,int index);
		void ClipPart(std::vector<Vertex>& vertecies, int index, float CF, std::vector<Vertex>& finalV);
};
