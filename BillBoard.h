#pragma once

#include "SceneNode.h"
#include <glm/glm.hpp>
#include "Player.h"
#include "Model.h"

using namespace std;
using namespace glm;

class BillBoard : public ModelNode
{
public:
	vec3 right;
	vec3 up;
	BillBoard(const string& name, const string texturePath) : ModelNode(name, texturePath) {
		// load model
		// load texture
		// load shader
		// load mesh
		LoadModelFromFile(texturePath);
		Player* player;
		
	}
	void Visualize(const mat4& transform) override;

};