#include "playercontroller.h"
#include "game.h"
#include "utils.h"
#include "mesh.h"
#include "texture.h"
#include "rendertotexture.h"
#include "shader.h"
#include "entitymesh.h"
#include "scene.h"
#include <math.h>
#include <cmath>
#include "utils.h"
#include "camera.h"


SDL_Joystick *joy = NULL;

double last_time = 0;
double time = 0;
long last_shot = 0;

PlayerController::PlayerController()
{

	if (SDL_NumJoysticks()> 0) {
		joy = SDL_JoystickOpen(0);
	}

	

}


PlayerController::~PlayerController()
{
}

void PlayerController::render(void) {

}

void PlayerController::update(double seconds_elapsed,int numc ) {

	float speed = seconds_elapsed * 100;
	time = seconds_elapsed;
	if (GameStage::instance->keystate[SDL_SCANCODE_LSHIFT])
		speed *= 25;


	if (joy) {

		JoystickState jst = getJoystickState(joy);

		if (jst.button[LB_BUTTON]) {
			speed *= 25;
		}

		if (abs(jst.axis[LEFT_ANALOG_X]) > 0.2)
		{
			Scene::instance->plane->model.rotateLocal(-jst.axis[LEFT_ANALOG_X] * seconds_elapsed, Vector3(0, 0, 1));
		}
		if (abs(jst.axis[RIGHT_ANALOG_Y]) > 0.2)
		{
			Scene::instance->plane->model.rotateLocal(jst.axis[RIGHT_ANALOG_Y] * seconds_elapsed, Vector3(1, 0, 0));
		}
	}

	if (GameStage::instance->keystate[SDL_SCANCODE_A] || GameStage::instance->keystate[SDL_SCANCODE_LEFT]) {
		Scene::instance->plane->model.rotateLocal(seconds_elapsed * 5, Vector3(0, 0, 1));
	}
	if (GameStage::instance->keystate[SDL_SCANCODE_D] || GameStage::instance->keystate[SDL_SCANCODE_RIGHT]) {
		Scene::instance->plane->model.rotateLocal(-seconds_elapsed * 5, Vector3(0, 0, 1));
	}
	if (GameStage::instance->keystate[SDL_SCANCODE_W] || GameStage::instance->keystate[SDL_SCANCODE_UP]) {
		Scene::instance->plane->model.rotateLocal(-seconds_elapsed, Vector3(1, 0, 0));

	}
	if (GameStage::instance->keystate[SDL_SCANCODE_S] || GameStage::instance->keystate[SDL_SCANCODE_DOWN]) {
		Scene::instance->plane->model.rotateLocal(seconds_elapsed, Vector3(1, 0, 0));

	}

	Scene::instance->plane->model.traslateLocal(0, 0, seconds_elapsed * 10 * speed);
	Scene::instance->plane->setLastPosition(Scene::instance->plane->getPosition());
	Scene::instance->plane->setPosition(Scene::instance->plane->model * Vector3(0,0,0));

	if (GameStage::instance->keystate[SDL_SCANCODE_L])
		Scene::instance->plane->shoot();
	
	

	Vector3 pos;
	
	switch (numc%4) {
		case 0:
			pos = Scene::instance->plane->model * Vector3(0, 5, -15);
			pos = GameStage::instance->camera->eye  * 0.9 + pos * 0.1;
			//pos = pos.normalize()*10 + Vector3(0, 5, -15);
			//pos = scene->plane->model * Vector3(1, 1, 1);
			//std::cout << pos.x-lastpos.x << ",    " << pos.y - lastpos.y << ",   " << pos.z - lastpos.z << std::endl;
			
			GameStage::instance->camera->lookAt(pos, Scene::instance->plane->model* Vector3(0, 0, 40), Scene::instance->plane->model.rotateVector(Vector3(0, 1, 0))); //position the camera and point to 0,0,0
			break;
		case 1:
			
			GameStage::instance->camera->lookAt(Scene::instance->plane->model * Vector3(0, 0.75, -1.5), Scene::instance->plane->model* Vector3(0, 0, 50), Scene::instance->plane->model.rotateVector(Vector3(0, 1, 0)));
			break;
		case 2:
			GameStage::instance->camera->lookAt(Scene::instance->plane->model * Vector3(1.5, 0, 0), Scene::instance->plane->model* Vector3(0, 0, 50), Scene::instance->plane->model.rotateVector(Vector3(0, 1, 0)));
			break;
		case 3:
			GameStage::instance->camera->lookAt(Scene::instance->plane->model * Vector3(-1.5, 0, 0), Scene::instance->plane->model* Vector3(0, 0, -50), Scene::instance->plane->model.rotateVector(Vector3(0, 1, 0)));
			break;
	}
}