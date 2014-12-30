#include "HeadersInclude.h"
Vertex::Vertex(Vector4f vertex)
{
	m_x = vertex.GetX();
	m_y = vertex.GetY();
	m_z = vertex.GetZ();
	m_w = vertex.GetW();
}

Vertex Vertex::PerspectiveDivide()
{
	return Vertex(Vector4f(m_x/m_w,m_y/m_w,m_z/m_w,m_w));
}

Vertex Vertex::ApplyTransformations(Matrix4f transformations)
{	
	Vertex newVertex = Vertex(transformations * this->GetVertex());
	return newVertex;
}

void Vertex::PrintToConsole(bool withEndLineAppended)
{
	if(withEndLineAppended)
		std::cout << "(" << m_x << "," << m_y << "," << m_z << "," << m_w << ")" << std::endl;
	else
		std::cout << "(" << m_x << "," << m_y << "," << m_z << "," << m_w << ")";
}
