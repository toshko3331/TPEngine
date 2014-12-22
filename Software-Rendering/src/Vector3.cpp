#include "OSSpecificDefine.h"
#include "Vector3.h"

Vector3::Vector3(Uint32 x,Uint32 y,Uint32 z) : m_x(x), m_y(y), m_z(z)
{

}

//Overloading all operators that can make sense when using vectors.

//Adition of vectors.
Vector3 Vector3::operator+(const Vector3& vec)
{
	return Vector3(m_x + vec.m_x,m_y + vec.m_y, m_z + vec.m_z);	
}
//Subtraction of vectors.
Vector3 Vector3::operator-(const Vector3& vec)
{
	return Vector3(m_x - vec.m_x , m_y - vec.m_y , m_z - vec.m_z);
}
//Dot product between two vectors.
Vector3 Vector3::operator*(const Vector3& multVec)
{
	return Vector3(m_x * multVec.m_x , m_y * multVec.m_y , m_z * multVec.m_z);
}
//Scalar multiplication.
Vector3 Vector3::operator*(const int scalar)
{
	return Vector3(scalar * m_x , scalar * m_y, scalar * m_z);
}
