#include "HeadersInclude.h"


Vector3f::Vector3f(float x,float y,float z) : m_x(x), m_y(y), m_z(z)
{

}

//Overloading all operators that can make sense when using vectors.

//Adition of vectors.
Vector3f Vector3f::operator+(const Vector3f& vec)
{
	return Vector3f(m_x + vec.m_x,m_y + vec.m_y, m_z + vec.m_z);	
}
//Subtraction of vectors.
Vector3f Vector3f::operator-(const Vector3f& vec)
{
	return Vector3f(m_x - vec.m_x , m_y - vec.m_y , m_z - vec.m_z);
}
//Dot product between two vectors.
Vector3f Vector3f::operator*(const Vector3f& multVec)
{
	return Vector3f(m_x * multVec.m_x , m_y * multVec.m_y , m_z * multVec.m_z);
}
//Scalar multiplication.
Vector3f Vector3f::operator*(const int scalar)
{
	return Vector3f(scalar * m_x , scalar * m_y, scalar * m_z);
}
