#include "Player.h"
#include <stdio.h>
#include <math.h>


// this is a player class, which is responsible for handling the player's movement, shooting, health and ammo.
// it also handles the gravity and the reload time of the player's weapon.


// constructor of the player class which takes a camera pointer as a parameter. 
// it initializes the health and ammo of the player and sets the player's position to the camera's position.
Player::Player(Camera* camera)
	: health_max(5), ammo_max(5)
{
	this->camera = camera;
	this->isInAir = false;
	this->yVelocity = 0.0f;

	this->health = 5;
	this->ammo = 5;
}
// movemnet method of the player class which takes an offset and a delta as parameters. 
// void Player::Move(glm::vec3 offset, float delta)
// {
// 	camera->ProcessKeyboard(Camera::RIGHT, delta, offset.x);
// 	camera->ProcessKeyboard(Camera::FORWARD, delta, offset.z);

// 	plNode->UpdateBoundingPosition(camera->pos);
// }

void Player::Move(glm::vec3 offset, float delta)
{
    // Assuming that offset.x and offset.z determine the direction of the movement
	int quantor = 1;
    if (offset.x > 0)
    {
        // move right
        camera->ProcessKeyboard(Camera::RIGHT, delta, quantor);
    }
    else if (offset.x < 0)
    {
        // move left
        camera->ProcessKeyboard(Camera::LEFT, delta, quantor);
    }

    if (offset.z > 0)
    {
        // move forward
        camera->ProcessKeyboard(Camera::FORWARD, delta, quantor);
    }
    else if (offset.z < 0)
    {
        // move backward
        camera->ProcessKeyboard(Camera::BACKWARD, delta, quantor);
    }

    plNode->UpdateBoundingPosition(camera->pos);
}

// look method of the player class which takes a motion as a parameter. look method is responsible for handling the player's look movement.

void Player::Look(glm::vec2 motion)
{
	camera->ProcessMouseMovement(motion.x, -motion.y, true);
}

/*
 Jump method of the player class. It is responsible for handling the player's jump movement.
*/
void Player::Jump()
{
	if (isInAir)
		return;
	// just add a velocity to the player's y axis and set the isInAir to true. 

	yVelocity = 2.0f;
	isInAir = true;
}

void Player::UpdateGravity(float delta)
{
	// after the player jumps, we need to update the player's position according to the gravity. 
	camera->pos.y += yVelocity * delta;
	yVelocity -= Gravity * delta;
	// check if the player is on the ground or not. if it is, set the yVelocity to 0 and set the isInAir to false.
	if (camera->pos.y < 0.01f)
	{
		camera->pos.y = 0;
		yVelocity = 0.0f;
		isInAir = false;
	}
	// update the bounding position of the player node.
	plNode->UpdateBoundingPosition(camera->pos);
	ReloadTick(delta);
}

// ReloadTick method of the player class which takes a delta as a parameter.

void Player::ReloadTick(float delta)
{
	if (ammo == 0)
	{
		reloadTicks += delta;
	}

	if (reloadTicks >= reloadMaxTicks)
	{
		reloadTicks = 0;
		ammo = ammo_max;
	}
}

// Shoot method of the player class which takes a bullet engine pointer as a parameter.

void Player::Shoot(BulletEngine* bEngine)
{
	if (ammo == 0)
	{
		// wait for reload
		return;
	}

	glm::vec3 direction;
	glm::vec3 orig = camera->pos;

	BulletEngine::ScreenCenterToWorldRay(camera->GetViewMatrix(), camera->GetProjectionMatrix(), direction);

	// increase orig a tiny bit, so it doesn't intersect with playernode
	//orig.x += 0.2 * direction.x;
	//orig.y += 0.2 * direction.y;
	//orig.z += 0.2 * direction.z;

	//printf("Direction: %f %f %f\n", direction.x, direction.y, direction.z);

	bEngine->Shoot(direction, orig, camera->yaw + YAW, camera->pitch); // lazy

	ammo--;
}

void Player::SetPlayerNode(PlayerNode* plNode)
{
	this->plNode = plNode;
}

void Player::DecreaseHealth()
{
	health--;
	if (health == 0)
	{
		// game over
		printf("GAME OVER!");
		exit(1);
	}
}

int Player::GetHealth()
{
	return health;
}

int Player::GetAmmo()
{
	return ammo;
}