#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include "framework.h"
#include <iostream>
#include "includes.h"
#include "bullet.h"
#include "mesh.h"
#include "entitycollider.h"
typedef int MAX_BULLETS_CAP;


class BulletManager
{
public:
	static BulletManager* instance;

	static BulletManager* getInstance() {
		return instance;
	}
	BulletManager();
	virtual ~BulletManager();

	//std::vector<Bullet> bullets_vector;
	//POOL mejor que vector
	Bullet bullets[1000];
	int last_pos;

	void render();
	void update(float elapsed_time);
	void shoot(Vector3 pos, Vector3 vel, float tl, float pow, Entity* author, int type);

};
#endif 