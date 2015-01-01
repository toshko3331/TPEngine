#include "HeadersInclude.h"

Gradients::Gradients(Vertex minYVertex,Vertex midYVertex,Vertex maxYVertex)
{
	m_oneOverZ[0] = 1.0f/minYVertex.GetW(); 
	m_oneOverZ[1] = 1.0f/midYVertex.GetW(); 
	m_oneOverZ[2] = 1.0f/maxYVertex.GetW(); 

	m_uOverZ[0] = minYVertex.GetU()/minYVertex.GetW();
	m_uOverZ[1] = midYVertex.GetU()/midYVertex.GetW();
	m_uOverZ[2] = maxYVertex.GetU()/maxYVertex.GetW();

	m_vOverZ[0] = minYVertex.GetV()/minYVertex.GetW();
	m_vOverZ[1] = midYVertex.GetV()/midYVertex.GetW();
	m_vOverZ[2] = maxYVertex.GetV()/maxYVertex.GetW();

	//We need to calculate the dc'/dx and dc'/dy for each gradient. Since the U,V,and Z coordinates are our gradients, we need to that for all theree.
	//Calculating the denominators for the gradients.
	dX = ((midYVertex.GetX() - minYVertex.GetX()) * (minYVertex.GetY() - maxYVertex.GetY())) - 
	     ((minYVertex.GetX() - maxYVertex.GetX()) * (midYVertex.GetY() - maxYVertex.GetY()));
	dY = -dX;
	
	//Calculating all of the numerators here.
	
	oneOverZX = CalcStepX(m_oneOverZ);
	oneOverZY = CalcStepY(m_oneOverZ);

	uOverZX = CalcStepX(m_oneOverZ);
	uOverZY = CalcStepY(m_oneOverZ);
	
	vOverZX = CalcStepX(m_oneOverZ);	
	vOverZY = CalcStepY(m_oneOverZ)
	
	//All the actual values.
	//Maybe just do it in the above?
	dOneOverZY =  
	dVOverZ = 
	dUOverZ = 
}

float CalcStepX(float* gradient)
{
	return ((gradient[1] - gradient[2]) * (m_minYVertex.GetY() - m_maxYVertex.GetY())) - ((gradient[0] - gradient[2]) * (m_midYVertex.GetY() - m_maxYVertex.GetY()));

}
float CalcStepY(float* gradient)
{
	return 	((gradient[1] - gradient[2]) * (m_minYVertex.GetX() - m_maxYVertex.GetX())) - ((gradient[0] - gradient[2]) * (m_midYVertex.GetX() - m_maxYVertex.GetX()));


}
