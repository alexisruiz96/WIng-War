#include "aicontroller.h"
#include "scene.h"


AIcontroller::AIcontroller()
{
	target = Scene::instance->plane->getPosition();
}


AIcontroller::~AIcontroller()
{
}

void AIcontroller::update(double seconds_elapsed)
{


	//Camera* cam = GameStage::getInstance()->camera;
	Vector3 origin = player_plane->getPosition();
	Vector3 to_target = target - origin;
	float distance = to_target.length();
	if (distance > 75)
	{
		Vector3 front = player_plane->model.rotateVector(Vector3(0, 0, 1));
		to_target.normalize();
		float cos_angle = 1.0 - front.dot(to_target);
		Vector3 axis = to_target.cross(front);

		Matrix44 inv = player_plane->model;
		inv.inverse();
		axis = inv.rotateVector(axis);
		player_plane->model.rotateLocal(cos_angle, axis);
	}

}

void AIcontroller::setPlane(AirPlane* pl)
{
	this->player_plane = pl;
}


