#include "aicontroller.h"
#include "scene.h"


AIcontroller::AIcontroller()
{
	target = Scene::instance->plane->getPosition();;
}


AIcontroller::~AIcontroller()
{
}

void AIcontroller::update(double seconds_elapsed)
{
	target = Scene::instance->plane->getPosition();

	//Camera* cam = GameStage::getInstance()->camera;
	Vector3 origin = ai_plane->getPosition();
	Vector3 to_target = target - origin;
	float distance = to_target.length();
	if (distance > 75)
	{
		Vector3 front = ai_plane->model.rotateVector(Vector3(0, 0, 1));
		to_target.normalize();
		float cos_angle = 1.0 - front.dot(to_target);
		Vector3 axis = to_target.cross(front);

		Matrix44 inv = ai_plane->model;
		inv.inverse();
		axis = inv.rotateVector(axis);
		ai_plane->model.rotateLocal(cos_angle, axis);
		
	}

	ai_plane->model.traslateLocal(0, 0, seconds_elapsed * 100);
}

void AIcontroller::setPlane(AirPlane* pl)
{
	this->ai_plane = pl;
}


