#include "game_entities.h"
#include "bulletmanager.h"
#include "aicontroller.h"


AirPlane::AirPlane(bool ia)
{
	last_shot = 0;
	isIA = ia;

	controller = NULL;

	if (ia)
	{
		controller = new AIcontroller();
		controller->setPlane(this);
	}

}
AirPlane::~AirPlane()
{

}

Vector3 AirPlane::getPosition() {
	return this->position;
}
void AirPlane::setPosition(Vector3 pos) {
	this->position = pos;
}

Vector3 AirPlane::getLastPosition() {
	return this->last_position;
}
void AirPlane::setLastPosition(Vector3 lastpos) {
	this->last_position = lastpos;
}




void AirPlane::update(double seconds_elapsed)
{
	if (!this->isIA) {
		colEsferas();

		Vector3 origin = getPosition();
		Vector3 direction = (getPosition() - getLastPosition()).normalize();
		Vector3 collision;

		float maxdist = direction.length();
		if (colVSStatics(origin, direction, collision, 0, maxdist)) {
			std::cout << "Colision con statico" << std::endl;
		}
	}
	else
		controller->update(seconds_elapsed);
		this->setLastPosition(this->getPosition());
		this->setPosition(this->model * Vector3(0, 0, 0));
}


void AirPlane::colEsferas()
{
	for (int i = 0; i < dynamic_colliders.size(); i++)
	{
		//multiply the center by the model to have it in world coordinates
		Matrix44 model = dynamic_colliders[i]->model;
		Vector3 center = dynamic_colliders[i]->mesh->header.center;
		float radius = dynamic_colliders[i]->mesh->header.radius;
		Matrix44 plane_m = this->model;										//model of our plane
		Vector3 plane_c = this->mesh->header.center;						//center of our plane
		float plane_r = this->getRadius();									//radius of our plane
		if ((model*center).distance(plane_m*plane_c) <= (radius + plane_r))	//calculate if distance between centers is less than the sum of the radius
			this->onCollision(dynamic_colliders[i]);
	}
}



void AirPlane::shoot() {


	if (getTime() > last_shot) {

		Vector3 v = this->model.rotateVector(Vector3(0, 0, 1000));
		BulletManager::instance->shoot(model * Vector3(2, 0.25, 0.25), v, 2.0, 5.00,this, 1);
		BulletManager::instance->shoot(model * Vector3(-2, 0.25, 0.25), v, 2.0, 5.00,this, 1);
		last_shot = getTime() + 200;
	}
}