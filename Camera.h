#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Terrain.h"

const float YAW = 90.0f; // -90
const float PITCH = 0.0f;
const float SPEED = 3.0f; // 0.8f
const float SENSITIVITY = 0.1f;

class Camera
{
public:
	enum CameraMovement {
		FORWARD,
		RIGHT,
		BACKWARD,
		LEFT
	};

	Terrain* terrain;

	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw;
	float pitch;

	float movementSpeed;
	float mouseSensitivity;

	float camZoom;
	float nearPlane;
	float farPlane;
	float aspectX;
	float aspectY;

	int wSize;
	int hSize;
	
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetOrthogonalMatrix();

	void ProcessKeyboard(CameraMovement camMov, float delta, int quantor);
	void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
	
	void SetProjectionMatrix(float camZoom, int wSize, int hSize, float nearPlane, float farPlane);
private:
	void updateCameraVectors();
	int gcm(int a, int b);
};


#endif