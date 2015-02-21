#pragma once
#include <math.h>

class Vector3f
{
	public:
		Vector3f(float x,float y,float z);

		//Operator Overloading.
		Vector3f operator+(const Vector3f& vec);	
		Vector3f operator-(const Vector3f& vec);
		Vector3f operator*(const Vector3f& multVec);
		Vector3f operator*(const int scalar);
		//TO BE IMPLIMENTED:=+,=-,=*(Dot Product),=*(Scalar) . 

		//Getters////
		float GetX() {return m_x;}
		float GetY() {return m_y;}
		float GetZ() {return m_z;}
		
		float GetLength();
		Vector3f GetNormalized();
		//Methods
		Vector3f Lerp(Vector3f x,float lerpAmount);
		Vector3f CrossProduct(Vector3f vec);
	private:
		float m_x;
		float m_y;
		float m_z;
};
