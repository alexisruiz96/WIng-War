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


	bool is_static;
	bool is_dynamic;

	EntityCollider();
	virtual ~EntityCollider();
	virtual void onCollision(EntityCollider*);
	void update(double dt);

	int hp;
	void setHp(int hp);
	int getHp();
	//setters
	void setStatic();
	void setDynamic();
	
	//getters
	bool isStatic();
	bool isDynamic();
	Vector3 getCenter();
	float getRadius();
	Mesh* getMesh();

	bool colVSStatics(Vector3 origin, Vector3 direction, Vector3& collision, float min_dist, float max_distance);

};

#endif