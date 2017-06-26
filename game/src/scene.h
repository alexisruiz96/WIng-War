#ifndef SCENE_H
#define SCENE_H


#include "game_entities.h"


class AirPlane;
class Scene
{
public:
	static Scene* instance;

	static Scene* getInstance() {
		return instance;
	}

	Scene();
	virtual ~Scene();

	Entity* root;

	AirPlane* plane;
	EntityCollider* suelo;
	EntityMesh* cielo;
	AirPlane* bomber;
	AirPlane* p38;
	AirPlane* p38a;
	EntityMesh* water;
	EntityMesh* cannon;
	Boat* barco;
	AircraftCarrier* aircar;
	AirPlane* bomber1;
	AirPlane* bomber2;


	void createScene();
};

#endif