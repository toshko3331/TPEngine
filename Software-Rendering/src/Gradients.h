#pragma once
#include "HeadersInclude.h"

class Gradients()
{

	public:

	private:
		Vertex m_minYVertex;
		Vertex m_midYVertex;
		Vertex m_maxYVertex;
		
		float m_OneOverZ[2];
		float m_UOverZ[2];
		float m_VOverZ[2];
		//Used for calculating the numeratior of the gradients equation.
		float CalcStepX(float* gradient);
		float CalcStepY(float* gradient);	
};
