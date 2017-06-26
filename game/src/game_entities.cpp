#include "game_entities.h"
#include "bulletmanager.h"
#include "aicontroller.h"
#include "stages/stage.h"
#include "scene.h"
#include "stages/endstage.h"
#include "bass.h"
#include "stages/gamestage.h"
#include "entitycollider.h"
AirPlane::AirPlane(bool ia)
{
	last_shot = 0;
	isIA = ia;
	isFB = false;
	controller = NULL;

	if (ia)
	{
		controller = new AIcontroller();
		controller->setPlane(this);
	}

	score = 0;
}
AirPlane::~AirPlane()
{

}

int AirPlane::getScore() {
	return this->score;
}

void AirPlane::setScore(int score) {
	this->score = score;
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




void AirPlane::update(float seconds_elapsed)
{
	if (!this->isIA) {

			colEsferas();

		
		Vector3 origin = getPosition();
		Vector3 direction = (getPosition() - getLastPosition()).normalize();
		Vector3 collision;

		float maxdist = direction.length();
		if (colVSStatics(origin, direction, collision, 0, maxdist)) {
			std::cout << "Colision con statico" << std::endl;
			//toDestroy.push_back(this);
			//deleteEntity();
			deleteAllColliders();
			toDestroy.push_back(Scene::instance->root);
			toDestroy.push_back(Scene::instance->cielo);
			deleteEntity();
			Stage::instance->current->onChange("endstage");
			GameStage::instance->stopMusic();
		}
	}
	else
		controller->update(seconds_elapsed);

	this->setLastPosition(this->getPosition());
	this->setPosition(this->model * Vector3(0, 0, 0));

	if (this->getHp() <= 0) {
	
		if (!this->isIA) {
			
			deleteAllColliders();
			toDestroy.push_back(Scene::instance->root);
			toDestroy.push_back(Scene::instance->cielo);
			deleteEntity();
			Stage::instance->current->onChange("endstage");
			GameStage::instance->stopMusic();
		}
		else {
			toDestroy.push_back(this);
			deleteCollider(this);
			deleteEntity();
			Scene::instance->plane->setScore(Scene::instance->plane->getScore() + this->getScore());
		}
	}
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
		if ((model*center).distance(plane_m*plane_c) <= (radius + plane_r)) {	//calculate if distance between centers is less than the sum of the radius
			if(this != dynamic_colliders[i])
			this->onCollision(dynamic_colliders[i]);
			GameStage::instance->stopMusic();

		}
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

std::vector<Vector3> rute;

Boat::Boat()
{
	actual = 0;

	rute.push_back(Vector3(259, -15, -3266));
	rute.push_back(Vector3(2136, -15, -2231));
	rute.push_back(Vector3(4287, -15, -495));
	rute.push_back(Vector3(6530, -15, -688));
	rute.push_back(Vector3(6610, -15, -315));
	rute.push_back(Vector3(6951, -15, 1667));
	rute.push_back(Vector3(3777, -15, 3066));
	rute.push_back(Vector3(604, -15, 3586));
	rute.push_back(Vector3(-2214, -15, 5420));

	musicon = false;
}

Boat::~Boat()
{

}

void Boat::update(float seconds_elapsed)
{

	this->setLastPosition(this->getPosition());
	this->setPosition(this->model * Vector3(0, 0, 0));

	if (this->getHp() <= 0) {
		EndStage::instance->succes = true;
		deleteAllColliders();
		toDestroy.push_back(Scene::instance->root);
		toDestroy.push_back(Scene::instance->cielo);
		deleteEntity();
		Stage::instance->current->onChange("endstage");
		GameStage::instance->stopMusic();
	}

	Vector3 origin = this->getPosition();
	Vector3 front = this->model.rotateVector(Vector3(0, 0, 1));
	Vector3 target = rute[actual];
	Vector3 to_target = target - origin;
	float dist = to_target.length();
	to_target.normalize();
	float cos_angle = 1.0 - front.dot(to_target);

	Vector3 axis = to_target.cross(front);

	Matrix44 inv = this->model;
	inv.inverse();
	axis = inv.rotateVector(axis);
	this->model.rotateLocal(cos_angle * seconds_elapsed, axis);
	
	if (dist <= 150.0)
	{
		actual++;
	}
	if (actual == 6)
		musicon = true;

	if (actual == 9) {
		deleteAllColliders();
		toDestroy.push_back(Scene::instance->root);
		deleteEntity();
		Stage::instance->current->onChange("endstage");
		GameStage::instance->stopMusic();
		std::cout << "Time: " << getTime() << std::endl;
	}

	this->model.traslateLocal(0, 0, seconds_elapsed * 100);
	
}

Vector3 Boat::getPosition() {
	return this->position;
}
void Boat::setPosition(Vector3 pos) {
	this->position = pos;
}

Vector3 Boat::getLastPosition() {
	return this->last_position;
}
void Boat::setLastPosition(Vector3 lastpos) {
	this->last_position = lastpos;
}


AircraftCarrier::AircraftCarrier()
{

}

AircraftCarrier::~AircraftCarrier()
{

}

void AircraftCarrier::update(float seconds_elapsed)
{
	this->setLastPosition(this->getPosition());
	this->setPosition(this->model * Vector3(0, 0, 0));

	if ((this->getPosition() - Scene::instance->barco->getPosition()).length() <= 100.0)
	{
		std::cout << "eoaksdko" << std::endl;
		deleteAllColliders();
		toDestroy.push_back(Scene::instance->root);
		deleteEntity();
		Stage::instance->current->onChange("endstage");
		GameStage::instance->stopMusic();
		std::cout << "Time: " << getTime() << std::endl;
	}
	
}


Vector3 AircraftCarrier::getPosition() {
	return this->position;
}
void AircraftCarrier::setPosition(Vector3 pos) {
	this->position = pos;
}

Vector3 AircraftCarrier::getLastPosition() {
	return this->last_position;
}
void AircraftCarrier::setLastPosition(Vector3 lastpos) {
	this->last_position = lastpos;
}