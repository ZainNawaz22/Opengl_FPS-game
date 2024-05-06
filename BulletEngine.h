#pragma once
#ifndef BULLETENGINE_H
#define BULLETENGINE_H

#include <glm/glm.hpp>
#include <vector>
#include "Model.h"
#include "Shader.h"
#include "SceneNode.h"

class Bullet
{
public:
	glm::vec3 position;
	glm::vec3 direction;
	float yaw;
	float pitch;

	bool clipped;
	SceneNode* intersectedNode;
};

class BulletEngine
{
public:
	BulletEngine(float clipX, float clipZ);

	void Update(float delta);

	void Visualize();

	static void ScreenCenterToWorldRay(glm::mat4 viewMatrix, glm::mat4 projMatrix, glm::vec3& outDir);
	
	void Shoot(glm::vec3 worldDirection, glm::vec3 origin, float yaw, float pitch);

private:
	std::vector<Bullet> shotBullets;

	const float ClipX;
	const float ClipZ;

	Model bulletModel;
	Shader* bulletShdr;

	const float BulletVelocity = 100.0f; //30 dbg 100 real
	const int ClipThreshold = 15.0f;
	const float BulletRaycastThreshold = 0.5f;

	float deltaClip = 0.0f;

	void FreeClippedBullets();
};



#endif
