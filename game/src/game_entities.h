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
	int score;

public:

	int getScore();
	void setScore(int score);
	AirPlane(bool ia = false);
	virtual ~AirPlane();

	AIcontroller* controller;
	
	Vector3 getPosition();
	void setPosition(Vector3 pos);

	Vector3 getLastPosition();
	void setLastPosition(Vector3 lastpos);

	void update(float seconds_elapsed);

	void colEsferas();
	//bool colVSStatics(Vector3 origin, Vector3 direction, Vector3& collision, float min_dist, float max_distance);

	void shoot();
	bool isFB;
	
};

class Boat : public EntityCollider
{
private:
	Vector3 position;
	Vector3 last_position;
	long last_shot;
	bool isIA;


public:
	Boat();
	virtual ~Boat();

	Vector3 getPosition();
	void setPosition(Vector3 pos);

	Vector3 getLastPosition();
	void setLastPosition(Vector3 lastpos);

	void update(float seconds_elapsed);

	int actual;
	bool ok;
	bool musicon;
	void colEsferas();
	//bool colVSStatics(Vector3 origin, Vector3 direction, Vector3& collision, float min_dist, float max_distance);

	void shoot();

};


class AircraftCarrier : public EntityCollider
{
private:
	Vector3 position;
	Vector3 last_position;
	long last_shot;
	bool isIA;


public:
	AircraftCarrier();
	virtual ~AircraftCarrier();

	Vector3 getPosition();
	void setPosition(Vector3 pos);

	Vector3 getLastPosition();
	void setLastPosition(Vector3 lastpos);

	void update(float seconds_elapsed);

	void shoot();

};
#endif