#include "HeadersInclude.h"
#include <vector>
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

void Object::AddTexel(float texel)
{
	m_texelCoords.push_back(texel);
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

void Object::InsertionSortTexelCoords()
{
	//This has to be called for the texel coordinates vector to have proper data.
	std::vector<float> sortedTexelCoords;
	//-1 is used as a starting point, because all vertex ids are above or = to 0. This means that every coordinate will return that it is bigger for -1, and therefore, we can use -1 to register as the beginning of the vector.
	sortedTexelCoords.insert(sortedTexelCoords.begin(),-1);
	
	for(std::vector<float>::iterator i = m_texelCoords.begin(); i != m_texelCoords.end();i++)
	{
		float texelCoord = m_texelCoords.at(3 * (*i));
		for(std::vector<float>::iterator k = m_texelCoords.begin(); k != m_texelCoords.end();k++)
		{
			
			std::vector<float>::iterator sortedTexelCoordsIndex;
			//Offeseting the sortedTexelCoords by + 1 because of the intial -1 value added to the beginning of the vector.
			*sortedTexelCoordsIndex = 3 * (*k) + 1;
			if(texelCoord > sortedTexelCoords[*sortedTexelCoordsIndex])
			{
				sortedTexelCoords.insert(sortedTexelCoordsIndex + 0,texelCoord);
				sortedTexelCoords.insert(sortedTexelCoordsIndex + 1,m_texelCoords.at(3 * (*i) + 1);
				sortedTexelCoords.insert(sortedTexelCoordsIndex + 2,m_texelCoords.at(3 * (*i) + 2));
			}
		}
	}
	//Removing the -1 value,
	sortedTexelCoords.erase(sortedTexelCoords.begin());
	//Pre-computing the size of the sortedTexelCoords since it will change.
	int vectorSize =  sortedTexelCoords.size();
	std::vector<float>::iterator i = m_texelCoords.begin();
	//Deleting all of the vertex id numbers since they are not necesarry, and will make working with the vector harder.
	for(int j = 0; j < vectorSize; j++)
	{
		*i = j * 3;
		sortedTexelCoords.erase(i);
	}
	//Assinging the array back to the real one.
	m_texelCoords = sortedTexelCoords;
}
