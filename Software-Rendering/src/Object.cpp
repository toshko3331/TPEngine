#include "HeadersInclude.h"

Object::Object() : m_eulerRotation(Vector3f(0,0,0)), m_worldPosition(Vector3f(0,0,0))
{
	m_objectName = "";
	m_textureName = "";
}

void Object::AddVertex(float vertex)
{
	m_vertecies.push_back(vertex);
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

void Object::SetObjectEulerRotation(float x, float y, float z)
{
	m_eulerRotation = Vector3f(x,y,z);
}
