#include "HeadersInclude.h"

TriangulatedMesh::TriangulatedMesh(Object* object)  : m_rawVertecies(object->GetVertexVector()) , m_faces(object->GetFaceVector())
{
	if(object == NULL)
	{
		//ErrorWriteToLog("Model could not be loaded.");
		return;
	}
	//Faces can be stored as Vector3f
	//for each facex
	//	store the vertecies in the order which they should be drawn in	
	//
	//Each face can be a vector3 triplet

	for(unsigned int i = 0; i < object->GetVertexVector().size()/4;i++)
	{
		const std::vector<float>& vertexVector = object->GetVertexVector();
		const std::vector<float>& texelVector = object->GetTexelVector();
		m_objectVertecies.push_back( Vertex(
			Vector4f(vertexVector.at(i+1),vertexVector.at(i+2),vertexVector.at(i+3),1),
			Vector2f(texelVector.at(i),texelVector.at(i+1))));
	}
/*
	//This function actually might not be even needed.
	for(int i = 0;i <= model.GetAmountOfFaces; i++)
		verteciesInOrder[i] = faces.GetVertex(i + 0)
		verteciesInOrder[i + 1] = faces.GetVertex(i + 1)
		verteciesInOrder[i + 2] = faces.GetVertex(i + 2)
	
	amountOfTriangles = AmountOfFaces;
*/
}

