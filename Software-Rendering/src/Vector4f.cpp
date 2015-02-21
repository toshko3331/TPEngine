#include "Vector4f.h"

Vector4f::Vector4f(float x,float y,float z,float w)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_w = w;
}

float Vector4f::GetLength()
{
	return (float)sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);		
}

Vector4f Vector4f::GetNormalized()
{
	float length = this->GetLength();
	
	return Vector4f(m_x/length,m_y/length,m_z/length,m_w/length); 
}

Vector4f Vector4f::Lerp(Vector4f x,float lerpAmount)
{
	return Vector4f(((x - *this) * lerpAmount) + *this);
}

Vector4f Vector4f::CrossProduct(Vector4f vec)
{
	float	x = vec.GetX();
	float	y = vec.GetY();
	float	z = vec.GetZ();

	return Vector4f(m_y * z - m_z * y,m_z * x - m_x * z,m_x * y - m_y * x,0);
}

//					//
//		Vector Arithmetic	//
//					//

//Additon of two vectors.
Vector4f Vector4f::operator+(const Vector4f& vec)
{
	return Vector4f(m_x+vec.m_x , m_y+vec.m_y , m_z+vec.m_z , m_w+vec.m_w) ;
}

//Subtraction of two vectors.
Vector4f Vector4f::operator-(const Vector4f& vec)
{
	return Vector4f(m_x-vec.m_x , m_y-vec.m_y , m_z-vec.m_z , m_w-vec.m_w);
}

//Dot product between two vectors.
Vector4f Vector4f::operator*(const Vector4f& multVec)
{
	return Vector4f(m_x*multVec.m_x , m_y*multVec.m_y , m_z*multVec.m_z , m_w*multVec.m_w);
}

//A scalar times a vector.
Vector4f Vector4f::operator*(const float scalar)
{
	return Vector4f(m_x*scalar , m_y*scalar , m_z*scalar , m_w*scalar) ;
}
