#pragma once
#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "SceneNode.h"
#include "Player.h"

class ZombieNode;

class Zombie
{
public:
	Zombie(TransformNode* trN, Player* n, BulletEngine* bulletEngine);

	void Update(float delta);
	void SetSceneNode(ZombieNode* zNode);

	void DecreaseHealth();
	int GetHealth();
private:

	TransformNode* transformN;
	ZombieNode* zombieN;
	Player* player;
	BulletEngine* bulletEngine;

	int health;

	float shootTicks = 0;
	float lockTicks = 0;
	float shootYaw = 0;
	const float shootTicksMax = 3;
	const float lockTicksMax = 0.5f;

	float fixedRot = 0.0f;
	float fixedYaw = 0.0f;

	glm::vec3 forwardVector;
	glm::vec3 previousForwardVector;
	glm::vec3 rotationalVector;
	glm::vec3 zombiePos;
	//glm::vec3 hand;

	void Shoot();
};

#endif