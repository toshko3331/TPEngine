#pragma once
#include "HeadersInclude.h"

class Vertex 
{
	public:
		Vertex(Vector4f vertex);
		//Getters.
		float GetX() { return m_x;}
		float GetY() { return m_y;}
		float GetZ() { return m_z;}
		float GetW() { return m_w;}
	private:
		float m_x;
		float m_y;
		float m_z;
		float m_w;
};
