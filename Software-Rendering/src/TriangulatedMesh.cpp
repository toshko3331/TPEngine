#include "HeadersInclude.h"

TriangulatedMesh::TriangulatedMesh(Object* object)  : m_rawVertecies(object->GetVertexVector()) , m_faces(object->GetFaceVector())
{
	if(object == NULL)
	{
		//ErrorWriteToLog("Model could not be loaded.");
		return;
	}

	for(unsigned int i = 0; i < object->GetVertexVector().size()/4;i++)
	{
		const std::vector<float>& vertexVector = object->GetVertexVector();
		const std::vector<float>& texelVector = object->GetTexelVector();
		m_objectVertecies.push_back( Vertex(
			Vector4f(vertexVector.at(i+1),vertexVector.at(i+2),vertexVector.at(i+3),1),
			Vector2f(texelVector.at(i+1),texelVector.at(i+2))));
	}
}

