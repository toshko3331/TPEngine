#include "HeadersInclude.h"

//Perspective camera.
Camera::Camera(int screenWidth,int fov,float aspectRatio,float zNear,float zFar,Matrix4f transformation ) : m_projectionMatrix(Matrix4f().InitializeIdentity().PerspectiveProjection(fov,aspectRatio,zNear,zFar))
{
	m_xRotation = 0;
	m_yRotation = 0;
	m_screenWidth = screenWidth;
	//TODO:Do arithmetic with the transofrmation matrix to the rotation and coordinate vectors.

}


//Orthographic camera.
//TODO:Implement this properly.
Camera::Camera(int width, int height, float zFar, float zNear,Matrix4f transformation) : m_projectionMatrix(Matrix4f().InitializeIdentity().OrthographicProjection(width,height,zFar,zNear))
{

	m_xRotation = 0;
	m_yRotation = 0;
	//TODO:Do arithemtic with the transformation matrix tot he rotation and coordiante vectors.

}

Matrix4f Camera::GetMatrix()
{
	//TODO:When quaternions are implemented, move the translation as the last transformation of the matrix being multiplied.
	return m_projectionMatrix * Matrix4f().InitializeIdentity().Translate(m_position).RotateAroundX(m_rotation.GetX()).RotateAroundY(m_rotation.GetY()).RotateAroundZ(m_rotation.GetZ());
}

void Camera::UpdateCamera(SDL_Event* event)
{
	if(event->type == SDL_MOUSEMOTION)
	{
		float sensitivity = -0.785;
/*		//Rotation in the X-Axis
		float camPitch = sensitivity * (m_screenHalfHeight - event->motion.x);
		//Rotation among the Y-Axis	
		float camYaw = sensitivity * (m_screenHalfWidth - event->motion.y);

		m_rotation = Vector3f(camYaw,camPitch,0);	
*/
		Sint32 currentX = event->motion.x;
		Sint32 currentY = event->motion.y;
		Sint32 xDifference = currentX - m_previousX;
		Sint32 yDifference = currentY - m_previousY;

		m_xRotation += xDifference;
		m_yRotation += yDifference;

	//	std::cout << "X: " << currentX << "Y: " << currentY << std::endl;

		if(yDifference < 0 && xDifference < 0){
			m_rotation = Vector3f(m_rotation.GetX() + -1 * sensitivity,m_rotation.GetY() + -1 * sensitivity,0);	
		}else if(yDifference < 0 && xDifference > 0)
			m_rotation = Vector3f(m_rotation.GetX() + -1 * sensitivity,m_rotation.GetY() + 1 * sensitivity,0);	
	 	else if(yDifference > 0 && xDifference < 0)
			m_rotation = Vector3f(m_rotation.GetX() + 1 * sensitivity,m_rotation.GetY() + -1 * sensitivity,0);
		else if(yDifference > 0 && xDifference < 0)
			m_rotation = Vector3f(m_rotation.GetX() + 1 * sensitivity,m_rotation.GetY() + 1 * sensitivity,0);	
		else if(yDifference == 0 && xDifference > 0)
			m_rotation = Vector3f(m_rotation.GetX(),m_rotation.GetY() + 1 * sensitivity,0);	
	 	else if(yDifference == 0 && xDifference < 0)
			m_rotation = Vector3f(m_rotation.GetX(),m_rotation.GetY() + -1 * sensitivity,0);
		else if(yDifference > 0 && xDifference == 0)
			m_rotation = Vector3f(m_rotation.GetX() + 1 * sensitivity,m_rotation.GetY(),0);
		else if(yDifference < 0 && xDifference == 0)
			m_rotation = Vector3f(m_rotation.GetX() + -1 * sensitivity,m_rotation.GetY(),0);
		else if(yDifference == 0 && xDifference == 0)
			m_rotation = Vector3f(m_rotation.GetX(),m_rotation.GetY(),0);
		//These following if statments allow us to keep spining infinetly with the mouse.	
		if(currentX == 0)
		{
			currentX = m_screenWidth - 2;
		}else if(currentX == m_screenWidth-1)
		{
			currentX = 1;
		}
		//TODO:Eventually restrain the Y-Rotation as well.
		m_previousX = currentX;
		m_previousY = currentY;
	
	}else if (event->type == SDL_KEYDOWN)
	{

		//Not working yet properly. We are going to need Quaternions first.
		float speedFactor = 0.2;
		if(event->key.keysym.sym == SDLK_w)
        	{
			m_position = Vector3f(m_position.GetX(),m_position.GetY(),m_position.GetZ() + speedFactor);
		}
		if(event->key.keysym.sym == SDLK_a)
		{
			m_position = Vector3f(m_position.GetX() + speedFactor,m_position.GetY(),m_position.GetZ());
		}
		if(event->key.keysym.sym == SDLK_s)
		{
			m_position = Vector3f(m_position.GetX(),m_position.GetY(),m_position.GetZ() - speedFactor);
		}
		if(event->key.keysym.sym == SDLK_d)
		{
			m_position = Vector3f(m_position.GetX() - speedFactor,m_position.GetY(),m_position.GetZ());
		}	
		if(event->key.keysym.sym == SDLK_UP)
		{
		//	m_cameraMatrix = m_cameraMatrix.Translate(Vector3f(0,0,0.3));
		}
		if(event->key.keysym.sym == SDLK_DOWN)
		{
		//	m_cameraMatrix = m_cameraMatrix.Translate(Vector3f(0,0,-0.3));
		}	
	}
}
