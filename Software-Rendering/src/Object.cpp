#include "HeadersInclude.h"
#include <vector>
Object::Object() : m_eulerRotation(Vector3f(0,0,0)), m_worldPosition(Vector3f(0,0,0)), m_scale(Vector3f(0,0,0))
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

void Object::AddNormal(float normal)
{
	m_normals.push_back(normal);
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

//This method intializes the final vertex vector that allows the drawing of the object to occur.
void Object::IntializeTriangulatedMesh()
{
	std::vector<float> texelVector;
	//Creating a new vector with the texelCoords that are withouth indexes so we can refrence them easier in the Vertex cration loop.
	for(unsigned int i = 0;i < m_texelCoords.size();i+=3)
	{		
		texelVector.push_back(m_texelCoords.at(i + 1));
		texelVector.push_back(m_texelCoords.at(i + 2));
	}	
	
	//Vertex creation loop
	for(unsigned int i = 0; i < m_vertecies.size();i+=4)
	{
		//We do this to save computation, also the reason why we just don't use 'i' is because the size of the vector is exactly half the size.
		int iDividedByTwo = i/2;
		
		m_objectVertecies.push_back(Vertex(
					Vector4f(m_vertecies.at(i+1),m_vertecies.at(i+2),m_vertecies.at(i+3),1),
					Vector2f(texelVector.at(iDividedByTwo),texelVector.at(iDividedByTwo+1))));
	}
}

void Object::BubbleSortTexelCoords()
{
	int swapCounter = 1;
	while(swapCounter != 0)
	{	
		swapCounter = 0;
		for(unsigned int i = 0; i < m_texelCoords.size()/3 - 1;i++)
		{
			//Check by the vertex id if they are in order.
			if(m_texelCoords.at(i * 3) > m_texelCoords.at((i+1) * 3))
			{
				std::swap(m_texelCoords.at((i * 3) + 0),m_texelCoords.at((i+1) * 3 + 0));
				std::swap(m_texelCoords.at((i * 3) + 1),m_texelCoords.at((i+1) * 3 + 1));
				std::swap(m_texelCoords.at((i * 3) + 2),m_texelCoords.at((i+1) * 3 + 2));
				swapCounter++;
			}
		}
	}
}

//Scraped, this is not working correctly, but will be kept here incase I want to fix it.
void Object::InsertionSortTexelCoords()
{
	//This has to be called for the texel coordinates vector to have proper data.
	std::vector<float> sortedTexelCoords;
	sortedTexelCoords.resize(m_texelCoords.size());
	//-1 is used as a starting point, because all vertex ids are above or = to 0. This means that every coordinate will return that it is bigger for -1, and therefore, we can use -1 to register as the beginning of the vector.
	std::cout << *(sortedTexelCoords.begin()) << std::endl;
	sortedTexelCoords.insert(sortedTexelCoords.begin(),-1);
	std::cout << (sortedTexelCoords.size()) << std::endl;
	std::vector<float>::iterator i = m_texelCoords.begin();
	std::advance(i,-1);
	for(;i!= m_texelCoords.end();i++)
	{
		float texelCoord = m_texelCoords.at(3 * (*i));
		std::vector<float>::iterator k = m_texelCoords.begin();
		std::vector<float>::iterator sortedTexelCoordsIndex = m_texelCoords.begin();
		std::advance(k,-1);
		std::advance(sortedTexelCoordsIndex,-1);
		for(;k != m_texelCoords.end();k++)
		{	
			//Offeseting the sortedTexelCoords by + 1 because of the intial -1 value added to the beginning of the vector.
			//std::advance(sortedTexelCoordsIndex,3);
			std::cout << "'i' is: " << *i << "\t'k' is: " << *k << std::endl;
			if(texelCoord > sortedTexelCoords.at(*sortedTexelCoordsIndex))
			{
				sortedTexelCoords.insert(sortedTexelCoordsIndex,texelCoord);
				std::advance(sortedTexelCoordsIndex,1);
				sortedTexelCoords.insert(sortedTexelCoordsIndex,m_texelCoords.at(3 * (*i) + 1));
				std::advance(sortedTexelCoordsIndex,1);
				sortedTexelCoords.insert(sortedTexelCoordsIndex,m_texelCoords.at(3 * (*i) + 2));
				std::advance(sortedTexelCoordsIndex,1);
				std::cout << "------------" << std::endl;
				for(unsigned int o = 0; o < sortedTexelCoords.size();o++)
				{
										
					std::cout << sortedTexelCoords[o] << std::endl;
								
				}
				std::cout << "------------" << std::endl;	
				break;
			}
		}
	}

	//Removing the -1 value,
	sortedTexelCoords.erase(sortedTexelCoords.begin());
	//Pre-computing the size of the sortedTexelCoords since it will change.
	int vectorSize =  sortedTexelCoords.size();
	std::vector<float>::iterator it = m_texelCoords.begin();
	std::advance(it,-3);
	std::cout << "I got here 2" << std::endl;
	//Deleting all of the vertex id numbers since they are not necesarry, and will make working with the vector harder.
	for(int j = 0; j < vectorSize; j++)
	{
		std::advance(it,3);
		sortedTexelCoords.erase(it);
	}
	//Assinging the array back to the real one.
	m_texelCoords = sortedTexelCoords;
}
