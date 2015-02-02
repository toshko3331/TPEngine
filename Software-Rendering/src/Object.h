#pragma once
#include "HeadersInclude.h"
#include <vector>
#include <string>

class Object
{
	public:
		Object();
		void AddVertex(float vertex);
		void AddFace(int face);
		void AddTexel(float texel);
		void SetObjectName(std::string objectName);
		void SetWorldPosition(float x, float y, float z);
		void SetObjectEulerRotation(float x, float y, float z);
		void SetTextureName(std::string textureName);
		void InsertionSortTexelCoords();
		void BubbleSortTexelCoords();
		void IntializeTriangulatedMesh();
		//Getters
		std::string GetObjectName(){ return m_objectName; } 
		std::string GetTextureName(){ return m_textureName; }
		Vector3f GetWorldPosition(){ return m_worldPosition; }
		Vector3f GetObjectEulerRotation(){ return m_eulerRotation; }
		const std::vector<float>& GetRawVertexVector() { return m_vertecies; }
		const std::vector<int>& GetFaceVector() { return m_faces; }
		const std::vector<float>& GetTexelVector() { return m_texelCoords; }
		std::vector<Vertex>& GetVertexVector() { return m_objectVertecies; }
	private:
		Vector3f m_eulerRotation;
		Vector3f m_worldPosition;
		std::string m_objectName;
		std::string m_textureName;
		std::vector<float> m_vertecies;
		std::vector<int> m_faces;
		std::vector<float> m_texelCoords;
		std::vector<Vertex> m_objectVertecies;
};
