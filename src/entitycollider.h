#ifndef ENTITYCOLLIDER_H
#define ENTITYCOLLIDER_H

#include "entitymesh.h"
#include "utils.h"
#include <math.h>
#include <cmath>
#include "includes.h"
#include <vector>


class EntityCollider : public EntityMesh
{
public:

	static std::vector<EntityCollider*> static_colliders;
	static std::vector<EntityCollider*> dynamic_colliders;


	//bool is_static;
	//bool is_dynamic;

	EntityCollider();
	virtual ~EntityCollider();
	virtual void onCollision(EntityCollider*);
	void update(double dt);

	//setters
	void setStatic();
	void setDynamic();
	
	//getters
	Vector3 getCenter();
	float getRadius();
	Mesh* getMesh();

};

#endif