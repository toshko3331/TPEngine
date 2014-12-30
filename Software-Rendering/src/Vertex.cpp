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
	return Vertex(Vector4f(m_x/m_w,m_y/m_w,m_z/m_w,1));
	
}

