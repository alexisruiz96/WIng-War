#include "entitycollider.h"

std::vector<EntityCollider*> EntityCollider::static_colliders;
std::vector<EntityCollider*> EntityCollider::dynamic_colliders;

EntityCollider::EntityCollider()
{
}


EntityCollider::~EntityCollider()
{
}

void EntityCollider::update(double seconds_elapsed) 
{
}

void EntityCollider::onCollision(EntityCollider *)
{

	std::cout << "Colisiona" << std::endl;
	
}

void EntityCollider::setStatic()
{
	static_colliders.push_back(this);
}

void EntityCollider::setDynamic()
{
	dynamic_colliders.push_back(this);
}

Vector3 EntityCollider::getCenter() 
{
	return mesh->header.center;
}

float EntityCollider::getRadius() 
{
	return mesh->header.radius;
}

Mesh* EntityCollider::getMesh()
{
	return mesh;
}



