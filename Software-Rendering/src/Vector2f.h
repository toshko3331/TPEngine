#pragma once
#include <math.h>

class Vector2f{
	
	public:
		Vector2f(float x, float y);
		//Getters
		float GetX(){ return m_x;}
		float GetY(){ return m_y;}
	
		Vector2f operator+(const Vector2f& vec);
		Vector2f operator-(const Vector2f& vec);
		Vector2f operator*(const Vector2f& multVec);
		Vector2f operator*(const float scalar);

		float GetLength();
		Vector2f GetNormalized();
		//Methods
		Vector2f Lerp(Vector2f x,float lerpAmount);
	private:
		float m_x;
		float m_y;
};

