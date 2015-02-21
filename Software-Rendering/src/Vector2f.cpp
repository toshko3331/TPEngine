#include "Vector2f.h"

Vector2f::Vector2f(float x, float y)
{
	m_x = x;
	m_y = y;
}

float Vector2f::GetLength()
{
	return (float)sqrt(m_x * m_x + m_y * m_y);		
}

Vector2f Vector2f::GetNormalized()
{
	float length = this->GetLength();

	return Vector2f(m_x/length,m_y/length); 
}

Vector2f Vector2f::Lerp(Vector2f x,float lerpAmount)
{
	return Vector2f(((x - *this) * lerpAmount) + *this);
}

//					//
//		Vector Arithmetic	//
//					//

//Additon of two vectors.
Vector2f Vector2f::operator+(const Vector2f& vec)
{
	return Vector2f(m_x+vec.m_x , m_y+vec.m_y);
}

//Subtraction of two vectors.
Vector2f Vector2f::operator-(const Vector2f& vec)
{
	return Vector2f(m_x-vec.m_x , m_y-vec.m_y);
}

//Dot product between two vectors.
Vector2f Vector2f::operator*(const Vector2f& multVec)
{
	return Vector2f(m_x*multVec.m_x , m_y*multVec.m_y);
}

//A scalar times a vector.
Vector2f Vector2f::operator*(const float scalar)
{
	return Vector2f(m_x*scalar , m_y*scalar);
}

