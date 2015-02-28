#include "Vector3f.h"

Vector3f::Vector3f(float x,float y,float z) : m_x(x), m_y(y), m_z(z)
{

}

float Vector3f::GetLength()
{
	return (float)sqrt(m_x * m_x + m_y * m_y + m_z * m_z);		
}

Vector3f Vector3f::GetNormalized()
{
	float length = this->GetLength();
	
	return Vector3f(m_x/length,m_y/length,m_z/length); 
}

Vector3f Vector3f::Lerp(Vector3f x,float lerpAmount)
{
	return Vector3f(((x - *this) * lerpAmount) + *this);
}

Vector3f Vector3f::CrossProduct(Vector3f vec)
{
	float	x = vec.GetX();
	float	y = vec.GetY();
	float	z = vec.GetZ();

	return Vector3f(m_y * z - m_z * y,m_z * x - m_x * z,m_x * y - m_y * x);
}

//				//
//	Vector Arithmetic 	//
//				//

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
Vector3f Vector3f::operator*(const float scalar)
{
	return Vector3f(scalar * m_x , scalar * m_y, scalar * m_z);
}
