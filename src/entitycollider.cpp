#include "entitycollider.h"

std::vector<EntityCollider*> EntityCollider::static_colliders;
std::vector<EntityCollider*> EntityCollider::dynamic_colliders;

EntityCollider::EntityCollider()
{
	is_static = false;
	is_dynamic= false;
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
	is_static = true;
}

void EntityCollider::setDynamic()
{
	dynamic_colliders.push_back(this);
	is_dynamic = true;
}

bool EntityCollider::isStatic() {
	return this->is_static;
}

bool EntityCollider::isDynamic() {
	return this->is_dynamic;
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

bool EntityCollider::colVSStatics(Vector3 origin, Vector3 direction, Vector3& collision, float min_dist, float max_distance)
{
	std::vector<EntityCollider *> colliders;
	colliders = static_colliders;

	for (int i = 0; i < colliders.size(); i++)
	{
		EntityCollider* collider = colliders[i];
		Mesh* mesh = collider->getMesh(); //if the mesh is not found jump
		if (!mesh) {
			continue;
		}

		CollisionModel3D* collision_model = collider->mesh->getCollisionModel3D();
		collision_model->setTransform(collider->model.m);

		if (!collision_model->rayCollision(origin.v, direction.v, true, 0.0, max_distance)) //if there is not any ray collision jump
		{
			continue;
		}

		collision_model->getCollisionPoint(collision.v, true);
		return true;
	}
	return false;

}

