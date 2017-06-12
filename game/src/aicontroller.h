#pragma once

#include "controller.h"
//#include "stage.h"
#include "game_entities.h"


class AirPlane;

class AIcontroller : public Controller
{
public:
	AIcontroller();
	~AIcontroller();

	Vector3 target;
	AirPlane* ai_plane;

	void update(double seconds_elapsed);
	void setPlane(AirPlane* pl);
};

