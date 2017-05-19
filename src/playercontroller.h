#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "includes.h"
#include "camera.h"
#include "scene.h"
#include "bulletmanager.h"


class PlayerController
{
public:
	PlayerController();
	~PlayerController();




	void render(void);
	void update(double seconds_elapsed);
	
	void camBack(Camera* camera);

	void update(double seconds_elapsed, Scene* scene, const Uint8* keystate, BulletManager* bm, Camera* cam, int numc);
};

#endif 