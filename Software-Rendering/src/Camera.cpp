#include "HeadersInclude.h"
#include "glm/glm.hpp"
#define GLM_FORCE_RADIANS
#define PI 3.14159265359
#include "glm/gtx/transform.hpp"
#include "util.h"

Camera::Camera(const float fov,const float aspectRatio,const float nearPlane,const float farPlane,const float* deltaTime): 
        m_projectionMatrix(glm::perspective((float)((fov * PI)/ 180),aspectRatio,nearPlane,farPlane)),m_deltaTime(deltaTime)
{
	

}

Matrix4f Camera::GetMatrix()
{
	Matrix4f ProjectionMatrix = Matrix4f().InitializeIdentity();	
	Matrix4f ViewMatrix = Matrix4f().InitializeIdentity();
	ProjectionMatrix.Mat4ToMatrix4f(m_projectionMatrix);

	glm::mat4 lookAt = glm::lookAt(m_positionVector,m_positionVector + m_directionVector,m_upVector);
	
	ViewMatrix.Mat4ToMatrix4f(lookAt);
	return ProjectionMatrix * ViewMatrix; 

}

void Camera::UpdateCamera(const SDL_Event* event,const int halfWidth,const int halfHeight)
{

	m_keyboardState = SDL_GetKeyboardState(NULL);
		
	SDL_GetMouseState(&m_mouseXPosition,&m_mouseYPosition);

	float cameraSpeed = 1.0f;
	float mouseSpeed = 0.05f; 
	
	if(event->type == SDL_MOUSEMOTION)
	{
		m_xAngle += (float)(mouseSpeed * (*m_deltaTime) * (halfWidth - m_mouseXPosition));
		m_yAngle += (float)(mouseSpeed * (*m_deltaTime) * (halfHeight - m_mouseYPosition));
		//Guards against flipping upside down
		if(m_yAngle >= 1)
		{
			m_yAngle = 1;
		}
		else if(m_yAngle <= -1)
		{
			m_yAngle = -1;
		}	
		
		m_directionVector = glm::vec3(cos(m_yAngle) * sin(m_xAngle),sin(m_yAngle),cos(m_yAngle) * cos(m_xAngle));
		m_rightVector = glm::vec3(sin(m_xAngle - 3.14f/2.0f),0,cos(m_xAngle - 3.14/2.0f));
		m_upVector = glm::cross(m_rightVector,m_directionVector);
	}
	if(event->type == SDL_KEYDOWN)
	{
		if(m_keyboardState[SDL_SCANCODE_W])
		{
			m_positionVector += m_directionVector * (*m_deltaTime) * cameraSpeed;
		}
		if(m_keyboardState[SDL_SCANCODE_S])
		{
			m_positionVector -= m_directionVector * (*m_deltaTime) * cameraSpeed;
		}
		if(m_keyboardState[SDL_SCANCODE_D])
		{
			m_positionVector += m_rightVector * (*m_deltaTime) * cameraSpeed;
		}
		if(m_keyboardState[SDL_SCANCODE_A])
		{
			m_positionVector -= m_rightVector * (*m_deltaTime) * cameraSpeed;
		}
	}
}

