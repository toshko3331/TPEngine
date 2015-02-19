#pragma once
#include "HeadersInclude.h"
#include <vector>
#include <string>

class Object
{
	public:
		Object();
		void AddFace(int face);
		void SetObjectName(const std::string objectName);
		void SetWorldPosition(float x, float y, float z);
		void SetEulerRotation(float x, float y, float z);
		void SetScale(float x, float y, float z);
		void SetTextureName(const std::string textureName);
		//Getters
		std::string GetObjectName(){ return m_objectName; } 
		std::string GetTextureName(){ return m_textureName; }
		Vector3f GetWorldPosition(){ return m_worldPosition; }
		Vector3f GetEulerRotation(){ return m_eulerRotation; }
		Vector3f GetScale() { return m_scale; } 
		const std::vector<int>& GetFaceVector() { return m_faces; }
	private:
		Vector3f m_eulerRotation;
		Vector3f m_worldPosition;
		Vector3f m_scale;
		std::string m_objectName;
		std::string m_textureName;
		std::vector<int> m_faces;
};
