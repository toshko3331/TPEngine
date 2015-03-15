#pragma once
#include "HeadersInclude.h"
#include "glm/glm.hpp"

class Camera{
	public:
		Camera(const float fov,const float aspectRatio, const float nearPlane,const float farPlane,const float* deltaTime);
		void UpdateCamera(const SDL_Event* event,const int halfWidth,const int halfHeight);
		//Getters
		Matrix4f GetMatrix();
	private:
		const Uint8* m_keyboardState = SDL_GetKeyboardState(NULL);

		int m_mouseXPosition,m_mouseYPosition;
	
		float m_xAngle = 3.14f;
		float m_yAngle = 0.0f;

		glm::vec3 m_positionVector = glm::vec3(0,0,5);
	
		glm::vec3 m_directionVector = glm::vec3(0,0,1);
		glm::vec3 m_rightVector = glm::vec3(1,0,0);
		glm::vec3 m_upVector = glm::vec3(0,1,0);
	
		glm::mat4 m_projectionMatrix;
		const float* m_deltaTime;
};
