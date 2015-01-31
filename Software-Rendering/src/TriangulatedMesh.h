#pragma once
#include "HeadersInclude.h"


class TriangulatedMesh
{
	public:
		TriangulatedMesh(Object* object);
		const std::vector<Vertex>& GetVertecies(){ return m_objectVertecies; }
		const std::vector<int>& GetFaces(){ return m_faces; }	
	private:
		std::vector<float> m_rawVertecies;
		std::vector<int> m_faces;
		std::vector<Vertex> m_objectVertecies;
};
