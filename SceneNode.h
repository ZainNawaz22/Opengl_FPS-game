#pragma once

#ifndef SCENENODE_H
#define SCENENODE_H

#include <glm/glm.hpp>
#include <vector>
#include "Model.h"
#include "Shader.h"
#include "BoundingObjects.h"

class SceneNode
{
public:
	SceneNode();
	SceneNode(const std::string& name);

	virtual void Visualize(const glm::mat4& transform) = 0;
	virtual void TraverseIntersection(const glm::vec3& orig, const glm::vec3& dir, std::vector<Intersection*>& hits) = 0;

	const std::string NodeName;
protected:
	static std::vector<SceneNode*> intersectPath;
};

extern SceneNode* SceneGraph;

class GroupNode : public SceneNode
{
public:
	GroupNode();
	GroupNode(const std::string& name);

	void AddNode(SceneNode* sn);
	void RemoveNode(SceneNode* sn);

	void Visualize(const glm::mat4& transform); // override
	void TraverseIntersection(const glm::vec3& orig, const glm::vec3& dir, std::vector<Intersection*>& hits); // override
protected:
	std::vector<SceneNode*> groups;
};

class TransformNode : public GroupNode
{
public:
	glm::vec3 rotateVector;
	glm::vec3 rotateVector2;
	glm::vec3 scaleVector;
	glm::vec3 translateVector;
	float rotateAngleRad;
	float rotateAngleRad2;

	TransformNode();
	TransformNode(const std::string& name);

	//void Rotate(glm::vec3 rotV, float angle);
	//void Scale(glm::vec3 scV);
	//void Translate(glm::vec3 trV);

	//void SetTransform(glm::mat4 tr);
	//glm::mat4 GetTransform();

	void Visualize(const glm::mat4& transform); // override
	void TraverseIntersection(const glm::vec3& orig, const glm::vec3& dir, std::vector<Intersection*>& hits); // override
private:
	//glm::mat4 transform;
};

class ModelNode : public SceneNode
{
public:
	ModelNode();
	ModelNode(const std::string& name);
	ModelNode(const std::string& name, const std::string& path);

	~ModelNode();

	void SetShader(Shader* sd);

	void Visualize(const glm::mat4& transform); // override
	void TraverseIntersection(const glm::vec3& orig, const glm::vec3& dir, std::vector<Intersection*>& hits); // override
	void LoadModelFromFile(const std::string& path);
	void SetTexture(const std::string& path);

protected:
	Model m;
	Shader* sdr;
	BoundingSphere* sphere = NULL;
	//BoundingBox* box = NULL;
private:
	

	void AutoLoadShader(const std::string& name);
};

#endif
