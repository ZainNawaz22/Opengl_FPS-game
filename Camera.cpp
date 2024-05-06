#include "Camera.h"

#include <stdio.h>

// this is the implementation of the camera class which is used to create the camera for the player


// this is the constructor of the camera class taking the position of the camera, the up vector, the yaw and the pitch of the camera
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	: front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY)
{
	pos = position;
	worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	updateCameraVectors();
}

// this is the constructor of the camera class taking the position of the camera, the up vector, the yaw and the pitch of the camera

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
	: front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY)
{
	pos = glm::vec3(posX, posY, posZ);
	worldUp = glm::vec3(upX, upY, upZ);
	this->yaw = yaw;
	this->pitch = pitch;
	updateCameraVectors();
}



// getview matrix is used to get the view matrix of the camera which is used to visualize the scene

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(pos, pos + front, up); //up
}

// getorthogonal matrix is used to get the orthogonal matrix

glm::mat4 Camera::GetOrthogonalMatrix()
{
	return glm::ortho(0.0f, (float)wSize, 0.0f, (float)hSize); // -1.0f, 1.0f
}

// this is the function used to process the keyboard input of the player and move the camera accordingly
// it takes the direction of the movement and the delta time and the quantor of the movement
// the quantor is used to move the camera faster or slower
//void Camera::ProcessKeyboard(CameraMovement direction, float delta, int quantor)
//{
//	float vel = delta * movementSpeed * quantor;
//	glm::vec3 frontL = glm::vec3(front);
//	frontL.y = 0;
//
//	switch (direction)
//	{
//	case FORWARD:
//		pos += frontL * vel;
//		break;
//	case RIGHT:
//		pos += right * vel;
//		break;
//	}
//}




void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constraintPitch)
{
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (constraintPitch)
	{
		if (pitch > 89.9f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	updateCameraVectors();
}


// getprojection matrix is used to get the projection matrix of the camera, used in visualizing the scene

glm::mat4 Camera::GetProjectionMatrix()
{
	float aspectRatio = aspectX / aspectY;
	return glm::perspective(camZoom, aspectRatio, nearPlane, farPlane);
}

// setProjectionMatrix is used to set the projection matrix of the camera it takes the zoom of the camera, the width and the height of the window
// the near and the far plane of the camera

void Camera::SetProjectionMatrix(float camZoom, int wSize, int hSize, float nearPlane, float farPlane)
{
	int r = gcm(wSize, hSize);
	aspectX = wSize / r;
	aspectY = hSize / r;

	this->camZoom = camZoom;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;

	this->wSize = wSize;
	this->hSize = hSize;
}
// gcm stands for greatest common divisor
int Camera::gcm(int a, int b)
{
	return (b == 0) ? a : gcm(b, a % b);
}
// this function is used to update the camera vectors
// it is used to update the front, right and up vectors of the camera
void Camera::updateCameraVectors()
{
	glm::vec3 frontL;
	frontL.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	frontL.y = sin(glm::radians(pitch));
	frontL.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(frontL);

	right = glm::normalize(glm::cross(front, worldUp)); 
	up = glm::normalize(glm::cross(right, front));
}

void Camera::ProcessKeyboard(CameraMovement direction, float delta, int quantor){
	float vel = delta * movementSpeed * quantor;
	glm::vec3 frontL = glm::vec3(front);
	frontL.y = 0;

	glm::vec3 newPos;

	switch (direction)
	{
	case FORWARD:
		newPos = pos + frontL * vel;
		break;
	
	case RIGHT:
		newPos = pos + right * vel;
		break;
	case LEFT:
		newPos = pos - right * vel;
		break;

	case BACKWARD:
		newPos = pos - frontL * vel;
		break;
	
	}

	if(terrain->IsWithinBounds(newPos, glm::vec2(-20, -20), 40))
		pos = newPos;
}
