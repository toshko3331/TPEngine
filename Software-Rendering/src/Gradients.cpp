#include "HeadersInclude.h"

Gradients::Gradients(Vertex minYVertex,Vertex midYVertex,Vertex maxYVertex)
{

	m_minYVertex = &minYVertex;
	m_midYVertex = &midYVertex;
	m_maxYVertex = &maxYVertex;

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
	float dX = ((midYVertex.GetX() - maxYVertex.GetX()) * (minYVertex.GetY() - maxYVertex.GetY())) - 
	     ((minYVertex.GetX() - maxYVertex.GetX()) * (midYVertex.GetY() - maxYVertex.GetY()));
	
	float dY = -dX;
	//Calculating all gradients below.
	m_oneOverZX = CalcStepX(m_oneOverZ)/dX;
	m_oneOverZY = CalcStepY(m_oneOverZ)/dY;

	m_uOverZX = CalcStepX(m_uOverZ)/dX;
	m_uOverZY = CalcStepY(m_uOverZ)/dY;
	
	m_vOverZX = CalcStepX(m_vOverZ)/dX;	
	m_vOverZY = CalcStepY(m_vOverZ)/dY;	
}

float Gradients::CalcStepX(float* gradient)
{
	//Calculates the numerator for the X step of the gradient.
	return ((gradient[1] - gradient[2]) * (m_minYVertex->GetY() - m_maxYVertex->GetY())) - ((gradient[0] - gradient[2]) * (m_midYVertex->GetY() - m_maxYVertex->GetY()));

}
float Gradients::CalcStepY(float* gradient)
{	
	//Calculates the numerator for the Y step of the gradient.
	return 	((gradient[1] - gradient[2]) * (m_minYVertex->GetX() - m_maxYVertex->GetX())) - ((gradient[0] - gradient[2]) * (m_midYVertex->GetX() - m_maxYVertex->GetX()));


}
