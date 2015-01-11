#include "HeadersInclude.h"
#include <math.h>
Edge::Edge(Gradients gradients,Vertex minYVertex,Vertex maxYVertex,int minYVertexIndex)
{
	//To get the starting x we use the formula ((x2 - x1)/(y2 - y1)) + x1  

	m_yBegin = ceil(minYVertex.GetY());
	m_yEnd = ceil(maxYVertex.GetY());
	//The amount by which we step our x.
	m_reciprocalSlope =  (maxYVertex.GetX() - minYVertex.GetX()) / (maxYVertex.GetY() - minYVertex.GetY()); 
	
	// This variable is created because we need to take into account the truncated
	// values of each mathematical operation that converts float to an int.
	// If we don't this can come and haunt us later in the program at unexpected times.
	float yApproxFloatError = m_yBegin - minYVertex.GetY(); 
	m_x = (m_reciprocalSlope * yApproxFloatError) + minYVertex.GetX();
	float xApproxFloatError = m_x - minYVertex.GetX();

	m_UOverZ = gradients.GetUOverZ(minYVertexIndex) +
		   gradients.GetUOverZXGradient() * xApproxFloatError + 
		   gradients.GetUOverZYGradient() * yApproxFloatError;
	m_UOverZGradient = gradients.GetUOverZYGradient() + gradients.GetUOverZXGradient() * m_reciprocalSlope;

	m_VOverZ = gradients.GetVOverZ(minYVertexIndex) +
	       	   gradients.GetVOverZXGradient() * xApproxFloatError + 
		   gradients.GetVOverZYGradient() * yApproxFloatError;
	m_VOverZGradient = gradients.GetVOverZYGradient() + gradients.GetVOverZXGradient() * m_reciprocalSlope;
	
	m_OneOverZ = gradients.GetOneOverZ(minYVertexIndex) +
		     gradients.GetOneOverZXGradient() * xApproxFloatError +
		     gradients.GetOneOverZYGradient() * yApproxFloatError;
	m_OneOverZGradient = gradients.GetOneOverZYGradient() + gradients.GetOneOverZXGradient() * m_reciprocalSlope;
}
void Edge::Step()
{
	//Step all of our gradients here.
	m_x = m_x + m_reciprocalSlope;
	m_UOverZ = m_UOverZ + m_UOverZGradient;
	m_VOverZ = m_VOverZ + m_VOverZGradient;
	m_OneOverZ = m_OneOverZ + m_OneOverZGradient;	
}
