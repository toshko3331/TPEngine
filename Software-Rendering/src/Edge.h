#pragma once
#include "HeadersInclude.h"

class Edge
{
	public:
		Edge(Vertex minYVertex,Vertex maxYVertex);
		void Step();
		float GetX(){return m_x;}
		int GetYStart(){return m_yBegin;}
		int GetYEnd(){return m_yEnd;}
		int GetXCeiling(){return m_xCeiling;}
		float GetReciprocalSlope(){return m_reciprocalSlope;} 
	private:
		int m_yBegin;
		int m_yEnd;

		float m_x;
		float m_xCeiling;
		float m_reciprocalSlope;
};
