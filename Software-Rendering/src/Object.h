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
		void SetObjectName(std::string objectName);
		void SetWorldPosition(float x, float y, float z);
		void SetObjectEulerRotation(float x, float y, float z);
		void SetTextureName(std::string textureName);
		//Getters
		std::string GetObjectName(){ return m_objectName; } 
		std::string GetTextureName(){ return m_textureName; }
		Vector3f GetWorldPosition(){ return m_worldPosition; }
		Vector3f GetObjectEulerRotation(){ return m_eulerRotation; }
		const std::vector<float>& GetVertexVector() { return m_vertecies; }
		const std::vector<int>& GetFaceVector() { return m_faces; }
	private:
		Vector3f m_eulerRotation;
		Vector3f m_worldPosition;
		std::string m_objectName;
		std::string m_textureName;
		std::vector<float> m_vertecies;
		std::vector<int> m_faces;
};
