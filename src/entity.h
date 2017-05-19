#ifndef ENTITY_H //macros to ensure the code is included once
#define ENTITY_H

#include "framework.h"
#include "includes.h"
#include <iostream>
#include <string>
#include "mesh.h"
#include "texture.h"
#include "camera.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	std::string name;
	Matrix44 model;
	int id;
	Entity* parent; //pointer to parent
	std::vector<Entity*> children; //pointers to childrens

	virtual void render(Camera* camera, Shader* shader);
	virtual void update(float elapsed_time);

	void addChild(Entity* ent);
	void removeChild(Entity* ent);
	Vector3 getPosition();

	Matrix44 getGlobalMatrix(); //returns transform in wolrd coordinates.
};
#endif
