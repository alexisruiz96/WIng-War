#ifndef BULLET_H //macros to ensure the code is included once
#define BULLET_H

#include "framework.h"
#include "includes.h"
#include <iostream>
#include <string>
#include "entity.h"

class Bullet
{
public:
	Bullet();
	virtual ~Bullet();
	Vector3 position;
	Vector3 last_position;
	Vector3 velocity;
	float ttl; //time to live
	float power;//damage of bullet
	Entity* author;//who has shot
	int type;
	bool hittedYet;

};

#endif