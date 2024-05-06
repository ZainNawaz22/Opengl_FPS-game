#include "SceneNode.h"
#include "ShaderLibrary.h"

SceneNode* SceneGraph = NULL;

std::vector<SceneNode*> SceneNode::intersectPath;

// ===SceneNode===
SceneNode::SceneNode() : NodeName("") 
{ 
	if (SceneGraph == NULL)
	{
		SceneGraph = this;
	}
}

SceneNode::SceneNode(const std::string& name) : NodeName(name) 
{
	if (SceneGraph == NULL)
	{
		SceneGraph = this;
	}
}

// ===GroupNode===
GroupNode::GroupNode() : SceneNode() { } 

GroupNode::GroupNode(const std::string& name) : SceneNode(name) { }

void GroupNode::AddNode(SceneNode* sn)
{
	groups.push_back(sn);
}

void GroupNode::RemoveNode(SceneNode* sn)
{
	for (auto it = groups.begin(); it != groups.end(); )
	{
		if (*it == sn)
		{
			it = groups.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void GroupNode::Visualize(const glm::mat4& transform) // override
{
	for (auto it = groups.begin(); it != groups.end(); ++it)
	{
		(*it)->Visualize(transform);
	}
}

void GroupNode::TraverseIntersection(const glm::vec3& orig, const glm::vec3& dir, std::vector<Intersection*>& hits) // override
{
	intersectPath.push_back(this);
	for (auto it = groups.begin(); it != groups.end(); ++it)
	{
		(*it)->TraverseIntersection(orig, dir, hits);
	}
	intersectPath.pop_back();
}

// ===TransformNode===
TransformNode::TransformNode()
{
	//transform = glm::mat4(1.0f); 
	rotateVector = glm::vec3(0.0f);
	rotateVector2 = glm::vec3(0.0f);
	scaleVector = glm::vec3(1.0f);
	translateVector = glm::vec3(0.0f);
	rotateAngleRad = 0.0f;
	rotateAngleRad2 = 0.0f;

}

TransformNode::TransformNode(const std::string& tr) : GroupNode(tr)
{
	//transform = glm::mat4(1.0f);
	rotateVector = glm::vec3(0.0f);
	rotateVector2 = glm::vec3(0.0f);
	scaleVector = glm::vec3(1.0f);
	translateVector = glm::vec3(0.0f);
	rotateAngleRad = 0.0f;
	rotateAngleRad2 = 0.0f;
}

void TransformNode::Visualize(const glm::mat4& transform) // override
{
	// stack matrices
	glm::mat4 localTransform = glm::mat4(1.0f);

	localTransform = glm::translate(localTransform, translateVector);
	if (rotateAngleRad2 != 0.0f)
		localTransform = glm::rotate(localTransform, rotateAngleRad2, rotateVector2);
	if (rotateAngleRad != 0.0f)
		localTransform = glm::rotate(localTransform, rotateAngleRad, rotateVector);
	localTransform = glm::scale(localTransform, scaleVector);

	glm::mat4 stackedTr = localTransform * transform;

	for (auto it = groups.begin(); it != groups.end(); ++it)
	{
		(*it)->Visualize(stackedTr);
	}
}

void TransformNode::TraverseIntersection(const glm::vec3& orig, const glm::vec3& dir, std::vector<Intersection*>& hits) // override
{
	intersectPath.push_back(this);
	for (auto it = groups.begin(); it != groups.end(); ++it)
	{
		(*it)->TraverseIntersection(orig, dir, hits);
	}
	intersectPath.pop_back();
}

// ===ModelNode===
ModelNode::ModelNode() : SceneNode() { }

ModelNode::ModelNode(const std::string& name) : SceneNode(name) { }

ModelNode::ModelNode(const std::string& name, const std::string& path) : SceneNode(name)
{
	LoadModelFromFile(path);
	AutoLoadShader(name);
}

ModelNode::~ModelNode()
{
	if (sphere != NULL)
	//if (box != NULL)
		delete sphere;
		//delete box;
}

void ModelNode::SetShader(Shader* sd)
{
	this->sdr = sd;
}

void ModelNode::AutoLoadShader(const std::string& name)
{
	this->sdr = ShaderLibrary::GetInstance()->GetShader(name);
}

void ModelNode::SetTexture(const std::string& path)
{
	Texture tex;
	GLuint texid;
	m.LoadTexture(path.c_str(), texid);
	tex.id = texid;
	tex.type = "material.texture_diffuse";
	tex.path = path;

	m.textures_loaded.push_back(tex);

}

void ModelNode::LoadModelFromFile(const std::string& path)
{
	m.LoadModel(path);
	// create sphere
	sphere = new BoundingSphere(this, m);
	//box = new BoundingBox(this, m);
}

void ModelNode::Visualize(const glm::mat4& transform)
{
	sdr->use();
	sdr->setMat4("model", transform);
	glm::mat3 normalMat = glm::transpose(glm::inverse(transform));
	sdr->setMat3("normalMat", normalMat);
	sphere->Transform(transform); // compromise, assume transform will not change when traversing for intersect since last visualize call
	//box->Transform(transform);
	m.Draw(*sdr);
}

void ModelNode::TraverseIntersection(const glm::vec3& orig, const glm::vec3& dir, std::vector<Intersection*>& hits)
{
	// traverse intersection...
	if (sphere == NULL)
	//if (box == NULL)
		return;

	Intersection* hit = new Intersection();
	if (sphere->CollidesWithRay(orig, dir, *hit))
	//if (box->CollidesWithRay(orig, dir, *hit))
	{
		hit->intersectionPath = intersectPath;
		hit->intersectionPath.push_back(this);
		hit->intersectedNode = this;
		hits.push_back(hit);
	}
	else
		delete hit;
}
