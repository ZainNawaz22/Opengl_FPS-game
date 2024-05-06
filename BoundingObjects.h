#pragma once

#ifndef BOUNDINGOBJECTS_H
#define BOUNDINGOBJECTS_H

#include <glm\glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <vector>

class Model;
class SceneNode;
class ModelNode;

struct Intersection
{
	//the intersection point in world space
	glm::vec3 point;
	//the distance between the the intersection ray origin and the intersection point
	float distance;
	ModelNode* intersectedNode;
	// how we reach from root node to intersected node
	std::vector<SceneNode*> intersectionPath;
};

class IBoundingVolume
{
public:
	virtual bool CollidesWithRay(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, Intersection& intersection) = 0;
};

class BoundingSphere : public IBoundingVolume
{
	//local center
	glm::vec3 center;
	float radius;
	//center in world coordinates after model transformation
	glm::vec3 worldCenter;
	//the radius after applied model scale transformations
	float worldRadius;

protected:
	//the node the bounding volume belongs to
	ModelNode* node;

public:
	BoundingSphere(ModelNode* gn, const Model& model);

	BoundingSphere(ModelNode* gn, const glm::vec3& pos, const float radius);

	const glm::vec3& GetCenter() const;

	const glm::vec3 GetWorldCenter() const;

	const float GetRadius() const;

	void Transform(const glm::mat4& model);

	void SetWorldCenter(const glm::vec3& center);

	bool CollidesWithRay(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, Intersection& hit);
};

class BoundingBox : public IBoundingVolume
{
private:
	glm::vec3 minPoint;
	glm::vec3 maxPoint;
protected:
	ModelNode* node;
public:
	BoundingBox(ModelNode* gn);

	BoundingBox(ModelNode* gn, const Model& model);

	void Transform(const glm::mat4& model);

	bool CollidesWithRay(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, Intersection& hit);

	glm::vec3 minPointWorld;
	glm::vec3 maxPointWorld;
};

#endif
