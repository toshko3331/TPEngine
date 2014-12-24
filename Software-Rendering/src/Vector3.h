#pragma once
#include "HeadersInclude.h"


class Vector3
{
	public:
		Vector3(Uint32 x,Uint32 y,Uint32 z);


		//Operator Overloading.
		Vector3 operator+(const Vector3& vec);	
		Vector3 operator-(const Vector3& vec);
		Vector3 operator*(const Vector3& multVec);
		Vector3 operator*(const int scalar);
		//TO BE IMPLIMENTED:=+,=-,=*(Dot Product),=*(Scalar) . 

		//Getters////
		Uint32 GetX() {return m_x;}
		Uint32 GetY() {return m_y;}
		Uint32 GetZ() {return m_z;}
		/////////////

	private:
		Uint32 m_x;
		Uint32 m_y;
		Uint32 m_z;
};
