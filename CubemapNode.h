#pragma once
#ifndef CUBEMAPNODE_H
#define CUBEMAP_H

#include "stb_image.h"
#include "SceneNode.h"

class CubemapNode
{
public:
	CubemapNode(const std::string& top, const std::string& left, const std::string& right, const std::string& bottom, const std::string& front, const std::string& back);

	void Visualize(); // override
private:
	unsigned int textureID;
	vector<std::string> faces;

	Shader* skyboxShader;
	
	void LoadCubemap();
	void CreateCube(GLuint& VBO);

	GLuint VAO;
};


#endif