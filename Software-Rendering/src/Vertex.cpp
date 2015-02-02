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
	return Vertex(Vector4f(m_x/m_w,m_y/m_w,m_z/m_w,m_w),Vector2f(m_u,m_v));
}

Vertex Vertex::ApplyTransformations(Matrix4f transformations)
{	
	return Vertex(transformations * this->GetVertex(),Vector2f(m_u,m_v));
	
}

void Vertex::PrintToConsole(bool withEndLineAppended)
{
	if(withEndLineAppended)
		std::cout << "(" << m_x << "," << m_y << "," << m_z << "," << m_w << ");Texel(" << m_u <<","<< m_v << ")"  << std::endl;
	else
		std::cout << "(" << m_x << "," << m_y << "," << m_z << "," << m_w << ");Texel(" << m_u <<","<< m_v << ")";
}

float Vertex::Normal(Vertex maxYVertex, Vertex minYVertex)
{
	return ((maxYVertex.GetX() - m_x) * (minYVertex.GetY() - m_y)) - ((minYVertex.GetX() - m_x) * (maxYVertex.GetY() - m_y));
}
