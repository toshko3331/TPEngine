#pragma once
#include "HeadersInclude.h"

class Vertex 
{
	public:
		Vertex(Vector4f vertex,Vector2f texel);
		//Getters.
		float GetX() { return m_x;}
		float GetY() { return m_y;}
		float GetZ() { return m_z;}
		float GetW() { return m_w;}
		Vector4f GetVertex(){ return Vector4f(m_x,m_y,m_z,m_w);}
		float	 GetU(){ return m_u;}
		float	 GetV(){ return m_v;}
		//Methods
		Vertex PerspectiveDivide();
		Vertex ApplyTransformations(Matrix4f transformations);
		void   PrintToConsole(bool withEndLineAppended);
		float  Normal(Vertex minYVertex,Vertex maxYVertex);	
	private:
		float m_x;
		float m_y;
		float m_z;
		float m_w;

		float m_u;
		float m_v;
};
