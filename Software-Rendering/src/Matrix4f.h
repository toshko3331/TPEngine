#pragma once
#include "HeadersInclude.h"

class Matrix4f
{
	public:
		Matrix4f();
		Matrix4f(float one, float two, float three, float four, float five ,float six, float seven, float eight, float nine, float ten, float eleven, float twelve, float thirteen, float fourteen, float fifteen, float sixteen);
		//Operator overloading
		Matrix4f operator*(const float scalar);
		Matrix4f operator*(Matrix4f matrix2);
		Vector4f operator*(Vector4f vector);
		//Getters
		float Get(short column, short row){return m_matrix[column][row];}
	private:
		float m_matrix[4][4];
};
