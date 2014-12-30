#pragma once
#include "HeadersInclude.h"

class Matrix4f
{
	public:
		Matrix4f();
		Matrix4f(float one, float two, float three, float four, float five ,float six, float seven, float eight, float nine, float ten, float eleven, float twelve, float thirteen, float fourteen, float fifteen, float sixteen);
		//Operator overloading
		Matrix4f operator*(const float scalar);
		Matrix4f operator*(const Matrix4f matrix2);
		Vector4f operator*(Vector4f vector);
		
		//Getters
		float Get(int column,int row) const {return m_matrix[column][row];} 
		//Methods
		Matrix4f InitializeIdentity();
		Matrix4f Scale(Vector3f vector);
		Matrix4f Translate(Vector3f vector);
		Matrix4f RotateAroundX(float angleInDegrees);
		Matrix4f RotateAroundY(float angleInDegrees);
		Matrix4f RotateAroundZ(float angleInDegrees);
		Matrix4f PerspectiveProjection(int fov,float aspectRatio, float zNear,float zFar);
		Matrix4f OrthographicProjection(int width, int height, float zFar, float zNear);
		Matrix4f WorldSpaceToScreenSpace(float halfWidth,float halfHeight);
		void PrintToConsole();	
		private:
		float** GetMatrix(); // This function might be obsolete.
		void Set(int column,int row,float value);
		void AssignMatrix(float** matrixBeingAssigned);// Make sure that we are deleteing this variable correctly. This function might be obsolete.
		float m_matrix[4][4];
};
