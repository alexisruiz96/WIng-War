#ifndef GAME_ENTITIES_H
#define GAME_ENTITIES_H

#include "entitycollider.h"


class AIcontroller;


class AirPlane : public EntityCollider
{
private:
	Vector3 position;
	Vector3 last_position;
	long last_shot;
	bool isIA;
	

public:
	AirPlane(bool ia = false);
	virtual ~AirPlane();

	AIcontroller* controller;
	int hp;
	Vector3 getPosition();
	void setPosition(Vector3 pos);

	Vector3 getLastPosition();
	void setLastPosition(Vector3 lastpos);

	void update(double seconds_elapsed);

	void colEsferas();
	//bool colVSStatics(Vector3 origin, Vector3 direction, Vector3& collision, float min_dist, float max_distance);

	void shoot();

	
};

#endif