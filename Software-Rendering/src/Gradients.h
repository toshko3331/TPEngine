#pragma once
#include "HeadersInclude.h"

class Gradients
{

	public:
		Gradients(Vertex minYVertex,Vertex midYVertex,Vertex maxYVertex);

		//Getters
		float GetOneOverZX{ return m_oneOverZX;}
		float GetOneOverZY{ return m_oneOverZY;}

		float GetUOverZX{ return m_uOverZX; }
		float GetUOverZX{ return m_uOverZY; }

		float GetVOverZX{ return m_vOverZX; }
		float GetVOverZY{ return m_vOverZY; }
		
		float* GetOneOverZ(){ return m_oneOverZ; }
		float* GetUOverZ(){ return m_uOverZ; }
		float* GetVOverZ(){ return m_vOverZ; } 
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
