#pragma once
#include "HeadersInclude.h"

class Edge
{
	public:
		Edge(Gradients gradients,Vertex minYVertex,Vertex maxYVertex,int minYVertexIndex);
		void Step();

		//Getters
		float GetX(){return m_x;}
		int GetYStart(){return m_yBegin;}
		int GetYEnd(){return m_yEnd;}
		float GetReciprocalSlope(){return m_reciprocalSlope;}
	
		float GetUOverZ(){return m_UOverZ;}
		float GetUOverZGradient(){return m_UOverZGradient;}

		float GetVOverZ(){return m_VOverZ;}
		float GetVOverZGradient(){return m_VOverZGradient;}

		float GetOneOverZ(){return m_OneOverZ;}
		float GetOneOverZGradient(){return m_OneOverZGradient;}

		float GetZBuffer(){return m_ZBuffer;}
		float GetZBufferGradient(){return m_ZBufferGradient;}

	private:
		int m_yBegin;
		int m_yEnd;
		float m_x;
		float m_reciprocalSlope;
		
		float m_UOverZ;
		float m_UOverZGradient;

		float m_VOverZ;
		float m_VOverZGradient;

		float m_OneOverZ;
		float m_OneOverZGradient;

		float m_ZBuffer;
		float m_ZBufferGradient;
};
