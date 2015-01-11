#pragma once
#include "HeadersInclude.h"

class Gradients
{

	public:
		Gradients(Vertex minYVertex,Vertex midYVertex,Vertex maxYVertex);

		//Getters
		float GetOneOverZXGradient(){ return m_oneOverZX;}
		float GetOneOverZYGradient(){ return m_oneOverZY;}

		float GetUOverZXGradient(){ return m_uOverZX; }
		float GetUOverZYGradient(){ return m_uOverZY; }

		float GetVOverZXGradient(){ return m_vOverZX; }
		float GetVOverZYGradient(){ return m_vOverZY; }
		
		float GetOneOverZ(short location){ return m_oneOverZ[location]; }
		float GetUOverZ(short location){ return m_uOverZ[location]; }
		float GetVOverZ(short location){ return m_vOverZ[location]; } 
	private:
		Vertex* m_minYVertex;
		Vertex* m_midYVertex;
		Vertex* m_maxYVertex;
		
		float m_oneOverZ[2];
		float m_uOverZ[2];
		float m_vOverZ[2];
	
		//Gradients	
		float m_oneOverZX;
		float m_oneOverZY;
		
		float m_uOverZX;
		float m_uOverZY;
		
		float m_vOverZX;
		float m_vOverZY;

		//Used for calculating the numeratior of the gradients equation.
		float CalcStepX(float* gradient);
		float CalcStepY(float* gradient);	
};
