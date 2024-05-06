#include "BulletEngine.h"
#include "ShaderLibrary.h"
#include <math.h>
#include "BoundingObjects.h"
#include "IDamageable.h"

// BulletEngine class is used to manage the bullets in the game and to perform raycasting

BulletEngine::BulletEngine(float clipX, float clipZ)
	: ClipX(clipX), ClipZ(clipZ)
	// BulletEngine constructor initializes the clipX and clipZ values and loads the bullet model
{
	// initialize the bullet velocity and the threshold values and reserve memory for the bullets
	// you can also change the bullet model and the shader
	bulletShdr = ShaderLibrary::GetInstance()->GetShader("bullet");
	bulletModel.LoadModel("./models/bullet_new/shareablebullet.obj");
	shotBullets.reserve(100);
}


// this function is used to shoot a bullet in the game it takes the world direction, the origin of the bullet and the yaw and pitch of the bullet
void BulletEngine::ScreenCenterToWorldRay(glm::mat4 viewMatrix, glm::mat4 projMatrix, glm::vec3& outDir)
{
	glm::vec4 lray_NDC(0.0f, 0.0f, 1.0f, 1.0f);

	glm::mat4 inverseProj = glm::inverse(projMatrix);
	glm::mat4 inverseView = glm::inverse(viewMatrix);

	glm::vec4 lray_camera = glm::vec4(inverseProj * lray_NDC);
	lray_camera.z = -1;
	lray_camera.w = 0;
	glm::vec4 lray_world = inverseView * lray_camera;

	outDir = glm::normalize(lray_world);
}

// this function is used to shoot a bullet in the game it takes the world direction, the origin of the bullet and the yaw and pitch of the bullet
// it also performs the raycasting and checks if the bullet intersects with any object in the game
void BulletEngine::Shoot(glm::vec3 worldDirection, glm::vec3 origin, float yaw, float pitch)
{
	Bullet blt;
	blt.direction = worldDirection;
	blt.position = origin;
	blt.clipped = false;
	blt.yaw = yaw;
	blt.pitch = pitch;
	// perform raycast from the origin of the bullet

	std::vector<Intersection*> inters;
	SceneGraph->TraverseIntersection(origin, worldDirection, inters);

	// if the bullet intersects with an object, find the minimum intersect and decrease the health of the object

	if (inters.size() > 0)
	{
		//printf("===Intersected!\n");

		// find minimum intersect
		Intersection* minIntersect = inters[0];

		for (auto i = inters.begin(); i != inters.end(); ++i)
		{
			if ((*i)->distance < minIntersect->distance)
			{
				minIntersect = *i;
			}
		}

		// print the path of the intersection

		std::vector<SceneNode*> path = minIntersect->intersectionPath;
		for (auto it = path.begin(); it != path.end(); ++it)
		{
			//printf("->%s", (*it)->NodeName.c_str());
		}
		//printf("\n");
		// set the intersected node and decrease the health of the object
		blt.intersectedNode = minIntersect->intersectedNode;

		IDamageable* damageable = dynamic_cast<IDamageable*>(minIntersect->intersectedNode);
		if (damageable != NULL)
		{
			damageable->DecreaseHealth();
		}
	}
	else
	{
		blt.intersectedNode = NULL;
	}

	shotBullets.push_back(blt);
}

void BulletEngine::Update(float delta)

{
	// update bullet positions
	for (auto it = shotBullets.begin(); it != shotBullets.end(); ++it)
	{
		if ((*it).clipped)
			continue;
		// move bullet in the direction of the bullet
		(*it).position += (*it).direction * delta * BulletVelocity;
		if (fabs((*it).position.x) > ClipX || fabs((*it).position.z) > ClipZ)
		{
			(*it).clipped = true;
			continue;
		}

		// perform raycast from current bullet position
		// if struck object doesn't match, clip bullet
		if (deltaClip >= BulletRaycastThreshold && (*it).intersectedNode != NULL)
		{
			std::vector<Intersection*> inters;
			SceneGraph->TraverseIntersection((*it).position, (*it).direction, inters);

			if (inters.size() > 0)
			{
				// find minimum intersect
				Intersection* minIntersect = inters[0];

				for (auto i = inters.begin(); i != inters.end(); ++i)
				{
					if ((*i)->distance < minIntersect->distance)
					{
						minIntersect = *i;
					}
				}

				if ((*it).intersectedNode != minIntersect->intersectedNode)
					(*it).clipped = true;
			}
			else if ((*it).intersectedNode != NULL)
			{ 
				(*it).clipped = true;
			}
		}
	}

	// free clipped bullets

	if (deltaClip >= ClipThreshold)
	{
		FreeClippedBullets();
		deltaClip = 0;
	}

	deltaClip += delta;
}

void BulletEngine::FreeClippedBullets()
{
	for (int i = 0; i < shotBullets.size(); i++)
	{
		// free clipped bullets
		if (!shotBullets[i].clipped)
			continue;

		shotBullets.erase(shotBullets.begin() + i);
	}
}

void BulletEngine::Visualize()
{
	// visualize the bullets in the game
	for (auto it = shotBullets.begin(); it != shotBullets.end(); ++it)
	{
		// if the bullet is clipped, don't visualize it
		if ((*it).clipped)
			continue;
		// visualize the bullet
		bulletShdr->use();
		glm::mat4 transformM = glm::translate(glm::mat4(1.0f), (*it).position);
		// rotate the bullet according to the yaw and pitch
		transformM = glm::rotate(transformM, glm::radians(-(*it).yaw), glm::vec3(0.0f, 1.0f, 0.0f)); 
		transformM = glm::rotate(transformM, glm::radians((*it).pitch), glm::vec3(1.0f, 0.0f, 0.0f));
		float scaleFactor = 0.01f; // replace with the desired scale factor
		transformM = glm::scale(transformM, glm::vec3(scaleFactor, scaleFactor, scaleFactor));

		bulletShdr->setMat4("model", transformM);


		bulletShdr->setVec3("color", 1.0f, 0.0f, 0.0f);
		bulletModel.Draw(*bulletShdr);
	}
}