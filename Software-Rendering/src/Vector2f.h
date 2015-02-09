#pragma once
#include "HeadersInclude.h"


class Vector2f{

	public:
		Vector2f(float x, float y);
		Vector2f Lerp(Vector2f x,float lerpAmount);
		//Getters
		float GetX(){ return m_x;}
		float GetY(){ return m_y;}
	
		Vector2f operator+(const Vector2f& vec);
		Vector2f operator-(const Vector2f& vec);
		Vector2f operator*(const Vector2f& multVec);
		Vector2f operator*(const float scalar);
	private:
	
		float m_x;
		float m_y;

};

