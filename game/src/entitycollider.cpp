#include "entitycollider.h"
#include "scene.h"
#include "stages/stage.h"

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
	deleteAllColliders();

	toDestroy.push_back(Scene::instance->root);
	toDestroy.push_back(Scene::instance->cielo);

	deleteEntity();

	Stage::instance->current->onChange("endstage");
	//Game::instance->render();

	
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

void EntityCollider::setHp(int hp)
{
	this->hp = hp;
}
int EntityCollider::getHp()
{
	return this->hp;
}

void EntityCollider::deleteCollider(Entity* e)
{
	auto ite = std::find(static_colliders.begin(), static_colliders.end(), e);

	if (ite != static_colliders.end())
		static_colliders.erase(ite);

	ite = std::find(dynamic_colliders.begin(), dynamic_colliders.end(), e);

	if (ite != dynamic_colliders.end())
		dynamic_colliders.erase(ite);


}

void EntityCollider::deleteAllColliders()
{
		/*auto ites = static_colliders.begin();
		static_colliders.erase(ites);
	
	int i = 0;
	for (std::vector<EntityCollider*>::iterator ited = dynamic_colliders.begin(); ited != dynamic_colliders.end(); ited++) {
		dynamic_colliders.erase(ited);
		i++;
	}*/

	static_colliders.clear();
	dynamic_colliders.clear();


}
