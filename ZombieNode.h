#pragma once
#ifndef ZOMBIENODE_H
#define ZOMBIENODE_H

#include "SceneNode.h"
#include "Zombie.h"
#include "IDamageable.h"

class ZombieNode : public ModelNode, public IDamageable
{
public:
	ZombieNode(Zombie* z);

	void Visualize(const glm::mat4& transform); 
	void TraverseIntersection(const glm::vec3& orig, const glm::vec3& dir, std::vector<Intersection*>& hits);
	void DecreaseHealth();
private:
	Zombie* zombie;
};


#endif