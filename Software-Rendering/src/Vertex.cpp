#include "HeadersInclude.h"

Vertex::Vertex(Vector4f vertex)
{
	m_x = vertex.GetX();
	m_y = vertex.GetY();
	m_z = vertex.GetZ();
	m_w = vertex.GetW();
}


