#pragma once
#ifndef TERRAIN_H
#define TERRAIN_H

#include "SceneNode.h"

class Terrain : public ModelNode
{
public:
	Terrain(glm::vec2 startPoint, int size);

	void Shoot(const glm::vec3& orig, const glm::vec3& dir);
	void Visualize(const glm::mat4& transform);
	bool IsWithinBounds(const glm::vec3& point, const glm::vec2& startPoint, int size);
private:
	Model GenerateTerrain(glm::vec2 startPoint, int size);
};

#endif


