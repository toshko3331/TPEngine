#include "HeadersInclude.h"


//Perspective camera.
Camera::Camera(int fov,float aspectRatio,float zNear,float zFar,Matrix4f transformation ) : m_cameraMatrix(Matrix4f().InitializeIdentity().PerspectiveProjection(fov,aspectRatio,zNear,zFar))
{
	m_cameraMatrix = m_cameraMatrix * transformation;
	m_typeOfProjection = 0;
}

//Orthographic camera.
Camera::Camera(int width, int height, float zFar, float zNear,Matrix4f transformation) : m_cameraMatrix(Matrix4f().InitializeIdentity().OrthographicProjection(width,height,zFar,zNear))
{
	m_cameraMatrix = m_cameraMatrix * transformation;
	m_typeOfProjection = 1;
}

void Camera::UpdateCamera(SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_LEFT)
        	{
			m_cameraMatrix = m_cameraMatrix.RotateAroundY(10 * 0.9);
		}
		if(event->key.keysym.sym == SDLK_RIGHT)
		{
			m_cameraMatrix = m_cameraMatrix.RotateAroundY(-10 * 0.9);
		}
	}
}
