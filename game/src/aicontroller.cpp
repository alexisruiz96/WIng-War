#include "aicontroller.h"
#include "scene.h"

bool isAWaypoint;

AIcontroller::AIcontroller()
{
	waypoints.push_back(Vector3(-3866, 1000, -2330));
	waypoints.push_back(Vector3(-4651, 1000, -524));
	waypoints.push_back(Vector3(-2155, 1000, 138));
	waypoints.push_back(Vector3(-1411, 1000, -1938));
	waypoints.push_back(Vector3(-14, 1000, -1668));
	waypoints.push_back(Vector3(-97, 1000, 539));
	waypoints.push_back(Vector3(2099, 1000, -1301));
	waypoints.push_back(Vector3(2684, 1000, -739));
	waypoints.push_back(Vector3(4894, 1000, 1092));

	isAWaypoint = true;
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


	if (ai_plane->isFB) {
		Vector3 p  = Scene::instance->barco->getPosition();
		target = Vector3(p.x, p.y + 215, p.z);
	}

	if ((Scene::instance->plane->getPosition() - origin).length() < 750.0f) {
		target = Scene::instance->plane->getPosition();
		isAWaypoint = false;
	}

	Vector3 front = ai_plane->model.rotateVector(Vector3(0, 0, 1));

	Vector3 to_target = target - origin;
	float distance = to_target.length();

	if (!isAWaypoint)
	{
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
	}
	else if(isAWaypoint && !ai_plane->isFB)
	{
		if (distance > 1000)
		{
			to_target.normalize();
			float cos_angle = 1.0 - front.dot(to_target);
			Vector3 axis = to_target.cross(front);

			Matrix44 inv = ai_plane->model;
			inv.inverse();
			axis = inv.rotateVector(axis);
			ai_plane->model.rotateLocal(cos_angle * seconds_elapsed * 10, axis);
		}
	}
	else if (isAWaypoint && ai_plane->isFB)
	{
		if (distance > 100)
		{
			to_target.normalize();
			float cos_angle = 1.0 - front.dot(to_target);
			Vector3 axis = to_target.cross(front);

			Matrix44 inv = ai_plane->model;
			inv.inverse();
			axis = inv.rotateVector(axis);
			ai_plane->model.rotateLocal(cos_angle * seconds_elapsed * 10, axis);
		}
	}

	float angle_with_target = 1 - front.dot(ai_plane->getPosition() - target);
	if (abs(angle_with_target) < 0.05 && distance < 400  && !isAWaypoint)
	{
		this->ai_plane->shoot();
	}

	ai_plane->model.traslateLocal(0, 0, seconds_elapsed * 125);
}

void AIcontroller::setPlane(AirPlane* pl)
{
	this->ai_plane = pl;
}


