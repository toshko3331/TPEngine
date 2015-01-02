#include "HeadersInclude.h"
Vertex::Vertex(Vector4f vertex,Vector2f texel)
{
	m_x = vertex.GetX();
	m_y = vertex.GetY();
	m_z = vertex.GetZ();
	m_w = vertex.GetW();
	
	m_u = texel.GetX();
	m_v = texel.GetY();
}

Vertex Vertex::PerspectiveDivide()
{
	return Vertex(Vector4f(m_x/m_w,m_y/m_w,m_z/m_w,m_w/m_w),Vector2f(m_u,m_v));
}

Vertex Vertex::ApplyTransformations(Matrix4f transformations)
{	
	Vertex newVertex = Vertex(transformations * this->GetVertex(),Vector2f(m_u,m_v));
	return newVertex;
}

void Vertex::PrintToConsole(bool withEndLineAppended)
{
	if(withEndLineAppended)
		std::cout << "(" << m_x << "," << m_y << "," << m_z << "," << m_w << ")" << std::endl;
	else
		std::cout << "(" << m_x << "," << m_y << "," << m_z << "," << m_w << ")";
}
