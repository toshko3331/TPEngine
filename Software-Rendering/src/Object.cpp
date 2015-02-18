#include "HeadersInclude.h"
#include <vector>
Object::Object() : m_eulerRotation(Vector3f(0,0,0)), m_worldPosition(Vector3f(0,0,0)), m_scale(Vector3f(1,1,1))
{
	m_objectName = "";
	m_textureName = "";
}

void Object::AddFace(int face)		
{
	m_faces.push_back(face);
}

void Object::SetObjectName(std::string objectName)
{
	m_objectName = objectName;
}

void Object::SetTextureName(std::string textureName)
{
	m_textureName = textureName;
}

void Object::SetWorldPosition(float x, float y, float z)
{
	m_worldPosition = Vector3f(x,y,z);
}

void Object::SetEulerRotation(float x, float y, float z)
{
	m_eulerRotation = Vector3f(x,y,z);
}

void Object::SetScale(float x, float y, float z)
{
	m_scale= Vector3f(x,y,z);
}
