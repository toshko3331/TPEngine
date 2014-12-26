#include "HeadersInclude.h"
#include <math.h>
Edge::Edge(Vertex minYVertex,Vertex maxYVertex)
{
	m_yBegin = ceil(minYVertex.GetY());
	m_yEnd = ceil(maxYVertex.GetY());
	m_reciprocalSlope =  (maxYVertex.GetX() - minYVertex.GetX()) / (maxYVertex.GetY() - minYVertex.GetY()); 
	
	// This variable is created because we need to take into account the truncated
	// values of each mathematical operation that converts float to an int.
	// If we don't this can come and haunt us later in the program at unexpected times.
	float yApproxFloatError = minYVertex.GetY() - m_yBegin; 
	m_x = (m_reciprocalSlope * yApproxFloatError) + minYVertex.GetX();

	m_xCeiling = ceil(m_x);
}

void Edge::Step()
{
	//Step all of our gradients here.
	m_x = m_x + m_reciprocalSlope;
	m_xCeiling = ceil(m_x);
	
	
}

