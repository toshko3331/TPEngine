#pragma once
#include "HeadersInclude.h"

class Camera{
	public:
		//Perspective camera.
		Camera(int fov,float aspectRatio,float zNear,float zFar,Matrix4f transformation = Matrix4f().InitializeIdentity());
		//Orthographic camera.
		Camera(int width, int height, float zFar, float zNear,Matrix4f transformation = Matrix4f().InitializeIdentity());
		void UpdateCamera(SDL_Event* event);
		//Getters
		Matrix4f& GetMatrix() { return m_cameraMatrix; }
		int GetTypeOfProjection() { return m_typeOfProjection; 
					//Returns 0 if Perspective
					//Returns 1 if Orthographic 
					}
	private:
		Matrix4f m_cameraMatrix;
		int m_typeOfProjection;	
};
