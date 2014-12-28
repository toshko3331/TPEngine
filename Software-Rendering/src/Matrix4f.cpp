#include "HeadersInclude.h"
#include <math.h>
#ifndef PI
#define PI 3.141592653589793
#endif

Matrix4f::Matrix4f()
{
	//Sets the matrix to the identity matrix.
	m_matrix[0][0] = 1;	m_matrix[1][0] = 0;	m_matrix[2][0] = 0;	m_matrix[3][0] = 0;
	
	m_matrix[0][1] = 0;	m_matrix[1][1] = 1;	m_matrix[2][1] = 0;	m_matrix[3][1] = 0;
	
	m_matrix[0][2] = 0;	m_matrix[1][2] = 0;	m_matrix[2][2] = 1;	m_matrix[3][2] = 0;
	
	m_matrix[0][3] = 0;	m_matrix[1][3] = 0;	m_matrix[2][3] = 0;	m_matrix[3][3] = 1;
}

Matrix4f::Matrix4f(float one, float two, float three, float four, float five ,float six, float seven, float eight, float nine, float ten, float eleven, float twelve, float thirteen, float fourteen, float fifteen, float sixteen)
{
	m_matrix[0][0] = one;		m_matrix[1][0] = two;		m_matrix[2][0] = three;		m_matrix[3][0] = four;
	
	m_matrix[0][1] = five;		m_matrix[1][1] = six;		m_matrix[2][1] = seven;		m_matrix[3][1] = eight;
	
	m_matrix[0][2] = nine;		m_matrix[1][2] = ten;		m_matrix[2][2] = eleven;	m_matrix[3][2] = twelve;
	
	m_matrix[0][3] = twelve;	m_matrix[1][3] = thirteen;	m_matrix[2][3] = fifteen;	m_matrix[3][3] = sixteen;
}

Matrix4f Matrix4f::operator*(const float scalar)
{
	//Multiplies everything by a scalar.
	return Matrix4f(
	m_matrix[0][0] * scalar,	m_matrix[1][0] * scalar,	m_matrix[2][0] * scalar,	m_matrix[3][0] * scalar,
	
	m_matrix[0][1] * scalar,	m_matrix[1][1] * scalar,	m_matrix[2][1] * scalar,	m_matrix[3][1] * scalar,
	
	m_matrix[0][2] * scalar,	m_matrix[1][2] * scalar,	m_matrix[2][2] * scalar,	m_matrix[3][2] * scalar,
	
	m_matrix[0][3] * scalar,	m_matrix[1][3] * scalar,	m_matrix[2][3] * scalar,	m_matrix[3][3] * scalar
	);
}

Matrix4f Matrix4f::operator*(Matrix4f matrix2)
{
	return Matrix4f(
	//First row of the new matrix.
	(m_matrix[0][0] * matrix2.Get(0,0)) + (m_matrix[0][0] * matrix2.Get(0,1)) + (m_matrix[0][0] * matrix2.Get(0,2)) + (m_matrix[0][0] * matrix2.Get(0,3)), 
	(m_matrix[1][0] * matrix2.Get(1,0)) + (m_matrix[1][0] * matrix2.Get(1,1)) + (m_matrix[1][0] * matrix2.Get(1,2)) + (m_matrix[1][0] * matrix2.Get(1,3)), 
	(m_matrix[2][0] * matrix2.Get(2,0)) + (m_matrix[2][0] * matrix2.Get(2,1)) + (m_matrix[2][0] * matrix2.Get(2,2)) + (m_matrix[2][0] * matrix2.Get(2,3)), 
	(m_matrix[3][0] * matrix2.Get(3,0)) + (m_matrix[3][0] * matrix2.Get(3,1)) + (m_matrix[3][0] * matrix2.Get(3,2)) + (m_matrix[3][0] * matrix2.Get(3,3)), 
	//Second row of the new matrix.
	(m_matrix[0][1] * matrix2.Get(0,0)) + (m_matrix[0][1] * matrix2.Get(0,1)) + (m_matrix[0][1] * matrix2.Get(0,2)) + (m_matrix[0][1] * matrix2.Get(0,3)), 
	(m_matrix[1][1] * matrix2.Get(1,0)) + (m_matrix[1][1] * matrix2.Get(1,1)) + (m_matrix[1][1] * matrix2.Get(1,2)) + (m_matrix[1][1] * matrix2.Get(1,3)), 
	(m_matrix[2][1] * matrix2.Get(2,0)) + (m_matrix[2][1] * matrix2.Get(2,1)) + (m_matrix[2][1] * matrix2.Get(2,2)) + (m_matrix[2][1] * matrix2.Get(2,3)), 
	(m_matrix[3][1] * matrix2.Get(3,0)) + (m_matrix[3][1] * matrix2.Get(3,1)) + (m_matrix[3][1] * matrix2.Get(3,2)) + (m_matrix[3][1] * matrix2.Get(3,3)), 
	//Third row of the new matrix.
	(m_matrix[0][2] * matrix2.Get(0,0)) + (m_matrix[0][2] * matrix2.Get(0,1)) + (m_matrix[0][2] * matrix2.Get(0,2)) + (m_matrix[0][2] * matrix2.Get(0,3)), 
	(m_matrix[1][2] * matrix2.Get(1,0)) + (m_matrix[1][2] * matrix2.Get(1,1)) + (m_matrix[1][2] * matrix2.Get(1,2)) + (m_matrix[1][2] * matrix2.Get(1,3)), 
	(m_matrix[2][2] * matrix2.Get(2,0)) + (m_matrix[2][2] * matrix2.Get(2,1)) + (m_matrix[2][2] * matrix2.Get(2,2)) + (m_matrix[2][2] * matrix2.Get(2,3)), 
	(m_matrix[3][2] * matrix2.Get(3,0)) + (m_matrix[3][2] * matrix2.Get(3,1)) + (m_matrix[3][2] * matrix2.Get(3,2)) + (m_matrix[3][2] * matrix2.Get(3,3)), 
	//Fourth row of the new matrix.
	(m_matrix[0][3] * matrix2.Get(0,0)) + (m_matrix[0][3] * matrix2.Get(0,1)) + (m_matrix[0][3] * matrix2.Get(0,2)) + (m_matrix[0][3] * matrix2.Get(0,3)), 
	(m_matrix[1][3] * matrix2.Get(1,0)) + (m_matrix[1][3] * matrix2.Get(1,1)) + (m_matrix[1][3] * matrix2.Get(1,2)) + (m_matrix[1][3] * matrix2.Get(1,3)), 
	(m_matrix[2][3] * matrix2.Get(2,0)) + (m_matrix[2][3] * matrix2.Get(2,1)) + (m_matrix[2][3] * matrix2.Get(2,2)) + (m_matrix[2][3] * matrix2.Get(2,3)), 
	(m_matrix[3][3] * matrix2.Get(3,0)) + (m_matrix[3][3] * matrix2.Get(3,1)) + (m_matrix[3][3] * matrix2.Get(3,2)) + (m_matrix[3][3] * matrix2.Get(3,3))
	);
}

Vector4f Matrix4f::operator*(Vector4f vector)
{
	return Vector4f( (m_matrix[0][0] * vector.GetX()) + (m_matrix[0][1] * vector.GetY()) + (m_matrix[0][2] * vector.GetZ()) + (m_matrix[0][3] * vector.GetW()),
			 (m_matrix[1][0] * vector.GetX()) + (m_matrix[1][1] * vector.GetY()) + (m_matrix[1][2] * vector.GetZ()) + (m_matrix[1][3] * vector.GetW()),
			 (m_matrix[2][0] * vector.GetX()) + (m_matrix[2][1] * vector.GetY()) + (m_matrix[2][2] * vector.GetZ()) + (m_matrix[2][3] * vector.GetW()),
			 (m_matrix[3][0] * vector.GetX()) + (m_matrix[3][1] * vector.GetY()) + (m_matrix[3][2] * vector.GetZ()) + (m_matrix[3][3] * vector.GetW())
			 );
}

void Matrix4f::Scale(Vector3f vector)
{
	m_matrix[0][0] = m_matrix[0][0] * vector.GetX();

	m_matrix[1][1] = m_matrix[1][1] * vector.GetY();
	
	m_matrix[2][2] = m_matrix[2][2] * vector.GetZ();
}

void Matrix4f::RotateAroundX(float angleInDegrees)
{
	float angleInRadians = angleInDegrees * PI / 180;	
	float cosOfAngle = cos(angleInRadians);
	float sinOfAngle = sin(angleInRadians);
	
	m_matrix[1][1] = m_matrix[1][1] * cosOfAngle;	m_matrix[2][1] = m_matrix[2][1] * -sinOfAngle;
	m_matrix[1][2] = m_matrix[1][2] * sinOfAngle;	m_matrix[2][2] = m_matrix[2][2] * cosOfAngle;
}

void Matrix4f::RotateAroundY(float angleInDegrees)
{
	float angleInRadians = angleInDegrees * PI / 180;	
	float cosOfAngle = cos(angleInRadians);
	float sinOfAngle = sin(angleInRadians);

	m_matrix[0][0] = m_matrix[0][0] * cosOfAngle;	m_matrix[2][0] = m_matrix[2][0] * sinOfAngle;
	m_matrix[0][2] = m_matrix[0][2] * -sinOfAngle;	m_matrix[2][2] = m_matrix[2][2] * cosOfAngle;
}

void Matrix4f::RotateAroundZ(float angleInDegrees)
{
	float angleInRadians = angleInDegrees * PI / 180;	
	float cosOfAngle = cos(angleInRadians);
	float sinOfAngle = sin(angleInRadians);

	m_matrix[0][0] = m_matrix[0][0] * cosOfAngle;	m_matrix[1][0] = m_matrix[1][0] * -sinOfAngle;
	m_matrix[0][1] = m_matrix[0][1] * sinOfAngle;	m_matrix[1][1] = m_matrix[1][1] * cosOfAngle;
}



























