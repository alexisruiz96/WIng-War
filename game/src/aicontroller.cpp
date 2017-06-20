#include "aicontroller.h"
#include "scene.h"


AIcontroller::AIcontroller()
{
	waypoints.push_back(Vector3(600, 500, 600));
	waypoints.push_back(Vector3(600, 500, -600));
	waypoints.push_back(Vector3(-600, 500, 600));
	waypoints.push_back(Vector3(1200, 500, 600));
	waypoints.push_back(Vector3(600, 500, 1200));
}


AIcontroller::~AIcontroller()
{
}

void AIcontroller::update(double seconds_elapsed)
{
	Vector3 target_front = Scene::instance->plane->model.rotateVector(Vector3(0, 0, 1));
	target_front.normalize();
	//Camera* cam = GameStage::getInstance()->camera;
	Vector3 origin = ai_plane->getPosition();

	target = waypoints[0];
	for (int i = 0; i < waypoints.size(); i++){
		if ((waypoints[i] - origin).length() < (target - origin).length())
			target = waypoints[i];
	}

	if ((Scene::instance->plane->getPosition() - origin).length() < 750.0f) {
		target = Scene::instance->plane->getPosition();
	}

	Vector3 front = ai_plane->model.rotateVector(Vector3(0, 0, 1));

	Vector3 to_target = target - origin;
	float distance = to_target.length();


	if (distance > 200)
	{
		to_target.normalize();
		float cos_angle = 1.0 - front.dot(to_target);
		Vector3 axis = to_target.cross(front);

		Matrix44 inv = ai_plane->model;
		inv.inverse();
		axis = inv.rotateVector(axis);
		ai_plane->model.rotateLocal(cos_angle * seconds_elapsed * 10, axis);
	}

	float angle_with_target = 1 - front.dot(target_front);
	if (angle_with_target < 0.1 && distance < 250)
	{
		this->ai_plane->shoot();
	}

	ai_plane->model.traslateLocal(0, 0, seconds_elapsed * 125);
}

void AIcontroller::setPlane(AirPlane* pl)
{
	this->ai_plane = pl;
}


