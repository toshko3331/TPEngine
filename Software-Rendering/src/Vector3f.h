#pragma once
#include "HeadersInclude.h"


class Vector3f
{
	public:
		Vector3f(float x,float y,float z);
		Vector3f Lerp(Vector3f x,float lerpAmount);

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
		/////////////

	private:
		float m_x;
		float m_y;
		float m_z;
};
