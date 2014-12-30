#include "HeadersInclude.h"
#include <math.h>
#ifndef PI
#define PI 3.141592653589793
#endif

Matrix4f::Matrix4f()
{

}

Matrix4f Matrix4f::InitializeIdentity()
{
	return (Matrix4f(
	1,	0,	0,	0,
	0,	1,	0,	0,
	0,	0,	1,	0,
	0,	0,	0,	1
	));
}

Matrix4f::Matrix4f(float one, float two, float three, float four, float five ,float six, float seven, float eight, float nine, float ten, float eleven, float twelve, float thirteen, float fourteen, float fifteen, float sixteen)
{
	m_matrix[0][0] = one;		m_matrix[1][0] = two;		m_matrix[2][0] = three;		m_matrix[3][0] = four;
	m_matrix[0][1] = five;		m_matrix[1][1] = six;		m_matrix[2][1] = seven;		m_matrix[3][1] = eight;
	m_matrix[0][2] = nine;		m_matrix[1][2] = ten;		m_matrix[2][2] = eleven;	m_matrix[3][2] = twelve;
	m_matrix[0][3] = thirteen;	m_matrix[1][3] = fourteen;	m_matrix[2][3] = fifteen;	m_matrix[3][3] = sixteen;
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

Matrix4f Matrix4f::operator*(const Matrix4f matrix2)
{
	return Matrix4f(
	//First row of the new matrix.
	(m_matrix[0][0] * matrix2.Get(0,0)) + (m_matrix[1][0] * matrix2.Get(0,1)) + (m_matrix[2][0] * matrix2.Get(0,2)) + (m_matrix[3][0] * matrix2.Get(0,3)), 
	(m_matrix[0][0] * matrix2.Get(1,0)) + (m_matrix[1][0] * matrix2.Get(1,1)) + (m_matrix[2][0] * matrix2.Get(1,2)) + (m_matrix[3][0] * matrix2.Get(1,3)), 
	(m_matrix[0][0] * matrix2.Get(2,0)) + (m_matrix[1][0] * matrix2.Get(2,1)) + (m_matrix[2][0] * matrix2.Get(2,2)) + (m_matrix[3][0] * matrix2.Get(2,3)), 
	(m_matrix[0][0] * matrix2.Get(3,0)) + (m_matrix[1][0] * matrix2.Get(3,1)) + (m_matrix[2][0] * matrix2.Get(3,2)) + (m_matrix[3][0] * matrix2.Get(3,3)), 
	//Second row of the new matrix.
	(m_matrix[0][1] * matrix2.Get(0,0)) + (m_matrix[1][1] * matrix2.Get(0,1)) + (m_matrix[2][1] * matrix2.Get(0,2)) + (m_matrix[3][1] * matrix2.Get(0,3)), 
	(m_matrix[0][1] * matrix2.Get(1,0)) + (m_matrix[1][1] * matrix2.Get(1,1)) + (m_matrix[2][1] * matrix2.Get(1,2)) + (m_matrix[3][1] * matrix2.Get(1,3)), 
	(m_matrix[0][1] * matrix2.Get(2,0)) + (m_matrix[1][1] * matrix2.Get(2,1)) + (m_matrix[2][1] * matrix2.Get(2,2)) + (m_matrix[3][1] * matrix2.Get(2,3)), 
	(m_matrix[0][1] * matrix2.Get(3,0)) + (m_matrix[1][1] * matrix2.Get(3,1)) + (m_matrix[2][1] * matrix2.Get(3,2)) + (m_matrix[3][1] * matrix2.Get(3,3)), 
	//Third row of the new matrix.
	(m_matrix[0][2] * matrix2.Get(0,0)) + (m_matrix[1][2] * matrix2.Get(0,1)) + (m_matrix[2][2] * matrix2.Get(0,2)) + (m_matrix[3][2] * matrix2.Get(0,3)), 
	(m_matrix[0][2] * matrix2.Get(1,0)) + (m_matrix[1][2] * matrix2.Get(1,1)) + (m_matrix[2][2] * matrix2.Get(1,2)) + (m_matrix[3][2] * matrix2.Get(1,3)), 
	(m_matrix[0][2] * matrix2.Get(2,0)) + (m_matrix[1][2] * matrix2.Get(2,1)) + (m_matrix[2][2] * matrix2.Get(2,2)) + (m_matrix[3][2] * matrix2.Get(2,3)), 
	(m_matrix[0][2] * matrix2.Get(3,0)) + (m_matrix[1][2] * matrix2.Get(3,1)) + (m_matrix[2][2] * matrix2.Get(3,2)) + (m_matrix[3][2] * matrix2.Get(3,3)), 
	//Fourth row of the new matrix.
	(m_matrix[0][3] * matrix2.Get(0,0)) + (m_matrix[1][3] * matrix2.Get(0,1)) + (m_matrix[2][3] * matrix2.Get(0,2)) + (m_matrix[3][3] * matrix2.Get(0,3)), 
	(m_matrix[0][3] * matrix2.Get(1,0)) + (m_matrix[1][3] * matrix2.Get(1,1)) + (m_matrix[2][3] * matrix2.Get(1,2)) + (m_matrix[3][3] * matrix2.Get(1,3)), 
	(m_matrix[0][3] * matrix2.Get(2,0)) + (m_matrix[1][3] * matrix2.Get(2,1)) + (m_matrix[2][3] * matrix2.Get(2,2)) + (m_matrix[3][3] * matrix2.Get(2,3)), 
	(m_matrix[0][3] * matrix2.Get(3,0)) + (m_matrix[1][3] * matrix2.Get(3,1)) + (m_matrix[2][3] * matrix2.Get(3,2)) + (m_matrix[3][3] * matrix2.Get(3,3))
	);
}

Vector4f Matrix4f::operator*(Vector4f vector)
{
	return Vector4f( (m_matrix[0][0] * vector.GetX()) + (m_matrix[1][0] * vector.GetY()) + (m_matrix[2][0] * vector.GetZ()) + (m_matrix[3][0] * vector.GetW()),
			 (m_matrix[0][1] * vector.GetX()) + (m_matrix[1][1] * vector.GetY()) + (m_matrix[2][1] * vector.GetZ()) + (m_matrix[3][1] * vector.GetW()),
			 (m_matrix[0][2] * vector.GetX()) + (m_matrix[1][2] * vector.GetY()) + (m_matrix[2][2] * vector.GetZ()) + (m_matrix[3][2] * vector.GetW()),
			 (m_matrix[0][3] * vector.GetX()) + (m_matrix[1][3] * vector.GetY()) + (m_matrix[2][3] * vector.GetZ()) + (m_matrix[3][3] * vector.GetW())
			 );
}

Matrix4f Matrix4f::Translate(Vector3f vector)
{
	Matrix4f translatedMatrix = Matrix4f().InitializeIdentity(); 

	translatedMatrix.Set(3,0,vector.GetX());
	translatedMatrix.Set(3,1,vector.GetY());
	translatedMatrix.Set(3,2,vector.GetZ());

	return ((*this) * translatedMatrix);
}

Matrix4f Matrix4f::Scale(Vector3f vector)
{
	Matrix4f scaledMatrix = Matrix4f().InitializeIdentity();

	scaledMatrix.Set(0,0,vector.GetX());
	scaledMatrix.Set(1,1,vector.GetY());
	scaledMatrix.Set(2,2,vector.GetZ());

	return ((*this) * scaledMatrix);
}

Matrix4f Matrix4f::RotateAroundX(float angleInDegrees)
{
	float angleInRadians = angleInDegrees * PI / 180;	
	float cosOfAngle = cos(angleInRadians);
	float sinOfAngle = sin(angleInRadians);

	Matrix4f rotatedMatrix = Matrix4f().InitializeIdentity();
		
	//Set the rotation matracies to the values that are needed to rotate around the X Axis.  
	rotatedMatrix.Set(1,1,cosOfAngle);	rotatedMatrix.Set(2,1,-sinOfAngle);
	rotatedMatrix.Set(1,2,sinOfAngle);	rotatedMatrix.Set(2,2,cosOfAngle);
	return ((*this) * rotatedMatrix);

}

Matrix4f Matrix4f::RotateAroundY(float angleInDegrees)
{
	float angleInRadians = angleInDegrees * PI / 180;	
	float cosOfAngle = cos(angleInRadians);
	float sinOfAngle = sin(angleInRadians);

	Matrix4f rotatedMatrix = Matrix4f().InitializeIdentity();
	
	//Set the rotation matracies to the values that are needed to rotate around the Y Axis.  
	rotatedMatrix.Set(0,0,cosOfAngle);	rotatedMatrix.Set(2,0,sinOfAngle);
	rotatedMatrix.Set(0,2,-sinOfAngle);	rotatedMatrix.Set(2,2,cosOfAngle);
	
	return ((*this) * rotatedMatrix);
}

Matrix4f Matrix4f::RotateAroundZ(float angleInDegrees)
{
	float angleInRadians = angleInDegrees * PI / 180;	
	float cosOfAngle = cos(angleInRadians);
	float sinOfAngle = sin(angleInRadians);

	Matrix4f rotatedMatrix = Matrix4f().InitializeIdentity();
	//Set the rotation matracies to the values that are needed to rotate around the Z Axis.  
	rotatedMatrix.Set(0,0,cosOfAngle);	rotatedMatrix.Set(1,0,-sinOfAngle);
	rotatedMatrix.Set(0,1,sinOfAngle);	rotatedMatrix.Set(1,1,cosOfAngle);
	
	return ((*this) * rotatedMatrix);
}

Matrix4f Matrix4f::PerspectiveProjection(int fov,float aspectRatio,float zNear,float zFar)
{
	float halfFOVTan = tan( (fov/2) );
	float zRange = zNear - zFar;
	
	Matrix4f perspectiveMatrix = Matrix4f().InitializeIdentity();

	perspectiveMatrix.Set(0,0,1/(halfFOVTan * aspectRatio));
	perspectiveMatrix.Set(1,1,1/halfFOVTan);
	perspectiveMatrix.Set(2,2,-1 * ((zFar + zNear) / zRange));
	perspectiveMatrix.Set(2,3, -1);
	perspectiveMatrix.Set(3,2,-1 * (2 * (zNear * zFar) /zRange));

	return (*this) * perspectiveMatrix;
}

Matrix4f Matrix4f::OrthographicProjection(int width, int height, float zFar, float zNear)
{
	
	float	zRange = zFar -zNear;
	
	Matrix4f orthographicMatrix = Matrix4f().InitializeIdentity();
	
	orthographicMatrix.Set(0,0,1/width);	orthographicMatrix.Set(1,1,1/height);
	orthographicMatrix.Set(2,2,-2/zRange);	orthographicMatrix.Set(3,2,-1 * ((zFar+zNear)/zRange));

	return (*this) * orthographicMatrix;
}

Matrix4f Matrix4f::WorldSpaceToScreenSpace(float halfWidth,float halfHeight)
{

	Matrix4f screenMatrix = Matrix4f().InitializeIdentity();

	screenMatrix.Set(0,0,halfWidth);
	screenMatrix.Set(1,1,-halfHeight);
	screenMatrix.Set(3,0,halfWidth - 0.5);
	screenMatrix.Set(3,1,halfHeight - 0.5);

	return (*this) * screenMatrix;
}

float** Matrix4f::GetMatrix()
{
	float** matrix = new float*[4];// = new float*;
	
	for(int i = 0; i < 4; i++)
	{
		matrix[i] = new float[4];
		for(int j = 0; j < 4; j++)
		{
			matrix[i][j] = m_matrix[i][j];	
		}

	}
	// THIS VARIABLE IS NOT DELETED ANYWHERE!!! This is the reason why this function is private.
	// Because AssignMatrix should delete it whcih is the only function that uses this function.
	// If any others use it, make sure that we delete this variable.
	return matrix;
}

void Matrix4f::AssignMatrix(float** matrixBeingAssigned)
{
	for(size_t i = 0;i < 4;i++)
	{
		for(size_t j = 0;j < 4;j++)
		{
			m_matrix[i][j] = matrixBeingAssigned[i][j];
		}
	}
	delete[] matrixBeingAssigned;
}

void Matrix4f::Set(int column,int row,float value)
{
	m_matrix[column][row] = value;
}

void Matrix4f::PrintToConsole()
{
	std::cout << "--- "	<< 		     "\t"  <<		       "\t" 		    <<   "\t"		        << "---" << std::endl;
	std::cout << "| "	<< m_matrix[0][0] << "\t" << m_matrix[1][0] << "\t" << m_matrix[2][0] << "\t" << m_matrix[3][0] << "  |" << std::endl;
	std::cout << "| " 	<< m_matrix[0][1] << "\t" << m_matrix[1][1] << "\t" << m_matrix[2][1] << "\t" << m_matrix[3][1] <<"   |" << std::endl;
	std::cout << "| "	<< m_matrix[0][2] << "\t" << m_matrix[1][2] << "\t" << m_matrix[2][2] << "\t" << m_matrix[3][2] <<"   |" << std::endl; 
	std::cout << "| "	<< m_matrix[0][3] << "\t" << m_matrix[1][3] << "\t" << m_matrix[2][3] << "\t" << m_matrix[3][3] <<"   |" << std::endl;
	std::cout << "--- "	<< 		     "\t"  <<		       "\t" 		    <<   "\t"		        << "---" << std::endl;
	
}

























