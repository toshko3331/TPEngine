#pragma once
#include "HeadersInclude.h"

class Camera{
	public:
		//Perspective camera.
		Camera(int screenWidth,int fov,float aspectRatio,float zNear,float zFar,Matrix4f transformation = Matrix4f().InitializeIdentity());
		//Orthographic camera.
		Camera(int width, int height, float zFar, float zNear,Matrix4f transformation = Matrix4f().InitializeIdentity());
		void UpdateCamera(SDL_Event* event);
		//Getters
		Matrix4f GetMatrix();
	private:
		
		int m_screenWidth;
		Matrix4f m_projectionMatrix;
		Sint32 m_previousX;
		Sint32 m_previousY;
		
		float m_xRotation;
		float m_yRotation;

		Vector3f m_rotation = Vector3f(0,0,0);
		Vector3f m_position = Vector3f(0,0,5);
};
