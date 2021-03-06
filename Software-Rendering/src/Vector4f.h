#pragma once
#include <math.h>

class Vector4f{
		
	public:
		Vector4f(float x,float y,float z,float w);
		//Operator Overloading to make it easier to work with the vectors in general.
		Vector4f operator+(const Vector4f& vec);
		Vector4f operator-(const Vector4f& vec);
		Vector4f operator*(const Vector4f& multVec);
		Vector4f operator*(const float scalar);
		//Getters for all of the variables.
		float GetX() {return m_x;}
		float GetY() {return m_y;}
		float GetZ() {return m_z;}
		float GetW() {return m_w;}
	 
		float GetLength();
		Vector4f GetNormalized();
		//Methods
		Vector4f Lerp(Vector4f x,float lerpAmount);
		Vector4f CrossProduct(Vector4f vec);
	private:
		float m_x;
		float m_y;
		float m_z;
		float m_w;
};
