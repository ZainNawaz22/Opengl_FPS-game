#include "ZombieNode.h"

ZombieNode::ZombieNode(Zombie* z)
	: ModelNode("zombie", "./models/zombie/Zombie.obj")
{
	zombie = z;
}

void ZombieNode::Visualize(const glm::mat4& transform)
{
	if (zombie->GetHealth() <= 0)
		return;

	ModelNode::Visualize(transform);
}

void ZombieNode::TraverseIntersection(const glm::vec3& orig, const glm::vec3& dir, std::vector<Intersection*>& hits)
{
	ModelNode::TraverseIntersection(orig, dir, hits);

	if (hits.size() > 0)
	{
		if (hits[hits.size() - 1]->intersectedNode == this)
		{
			zombie->DecreaseHealth();
		}
	}

}

void ZombieNode::DecreaseHealth()
{
	zombie->DecreaseHealth();
}