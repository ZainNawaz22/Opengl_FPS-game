#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "SceneNode.h"
#include <glm/glm.hpp>
#include "Camera.h"
#include "BulletEngine.h"
#include "PlayerNode.h"

class Player
{
public:
	Camera* camera;

	Player(Camera* camera);

	void SetPlayerNode(PlayerNode* plNode);

	void Move(glm::vec3 offset, float delta);
	void Jump();
	void Look(glm::vec2 motion);
	void Shoot(BulletEngine* bEngine);

	void UpdateGravity(float delta);

	int GetHealth();
	int GetAmmo();

	void DecreaseHealth();

	const int ammo_max;
	const int health_max;
private:
	float yVelocity;

	PlayerNode* plNode;
	
	const float Gravity = 5.0f;

	float reloadTicks = 0;

	const int reloadMaxTicks = 5;

	bool isInAir;

	void ReloadTick(float delta);

	int health;
	int ammo;
};


#endif
