#include "stages.h"
float angle = 0;
Scene* scene = NULL;
Shader * shader = NULL;

bool control_camera = false;
int cam_position = 0;
int numcam = 0;

PlayerController* pc = NULL;
GameStage* GameStage::instance = NULL;

std::map<std::string, Stage*> s_Stages;


void Stage::onChange(const char* stagename)
{

	std::map<std::string, Stage*>::iterator it = s_Stages.find(stagename);
	if (it != s_Stages.end())
		current = it->second;
}
MenuStage::MenuStage()
{
	
}
void MenuStage::init() 
{
	
}
void MenuStage::render()
{
	//set the clear color (the background color)
	glClearColor(0, 0, 1, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}
void MenuStage::update(double dt)
{

}

void MenuStage::onKeyPressed(SDL_KeyboardEvent event)
{

}
void MenuStage::onMouseButton(SDL_MouseButtonEvent event)
{
	this->current->onChange("gamestage");
}

GameStage::GameStage()
{
	instance = this;
	keystate = NULL;
}

void GameStage::init()
{
	camera = new Camera();
	camera->lookAt(Vector3(0.f, 25.f, 25.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f)); //position the camera and point to 0,0,0
	camera->setPerspective(70.f, Game::instance->window_width / (float)Game::instance->window_height, 0.1f, 100000.f); //set the projection, we want to be perspective


	//std::cout << scene->plane->model << std::endl;

	//test = new EntityMesh();
	//test->config("data/meshes/spitfire/spitfire_color_spec.tga", "data/meshes/spitfire/spitfire.ASE");
	scene = new Scene();
	scene->createScene();

	BulletManager::instance = new BulletManager();

	pc = new PlayerController();

}

void GameStage::render()
{
	//set the clear color (the background color)
	glClearColor(0.15, 0.30, 0.35, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Put the camera matrices on the stack of OpenGL (only for fixed rendering)
	camera->set();

	//Draw out world
	//drawGrid(500); //background grid

	glDisable(GL_DEPTH_TEST);
	scene->cielo->model.setIdentity();
	scene->cielo->model.traslate(camera->eye.x, camera->eye.y, camera->eye.z);
	scene->cielo->render(camera, shader);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);

	scene->root->render(camera, shader);
	//camera pos
	//std::cout << camera->eye.x << " - " << camera->eye.y << " - " << camera->eye.z << std::endl; 

	glDisable(GL_BLEND);

	BulletManager::instance->render();
}

void GameStage::update(double seconds_elapsed)
{
	keystate = Game::instance->keystate;

	float speed = seconds_elapsed * 100; //the speed is defined by the seconds_elapsed so it goes constant

										 //mouse input to rotate the cam
	if ((Game::instance->mouse_state & SDL_BUTTON_LEFT) || Game::instance->mouse_locked) //is left button pressed?
	{
		camera->rotate(Game::instance->mouse_delta.x * 0.005f, Vector3(0.0f, -1.0f, 0.0f));
		camera->rotate(Game::instance->mouse_delta.y * 0.005f, camera->getLocalVector(Vector3(-1.0f, 0.0f, 0.0f)));
	}

	//async input to move the camera around
	if (control_camera)
	{
		if (keystate[SDL_SCANCODE_LSHIFT]) speed *= 100; //move faster with left shift
		if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP]) camera->move(Vector3(0.0f, 0.0f, 1.0f) * speed);
		if (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN]) camera->move(Vector3(0.0f, 0.0f, -1.0f) * speed);
		if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT]) camera->move(Vector3(1.0f, 0.0f, 0.0f) * speed);
		if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT]) camera->move(Vector3(-1.0f, 0.0f, 0.0f) * speed);
	}
	else
	{
		//Vector3 lastpos = scene->plane->model * Vector3(1, 1, 1);

		BulletManager::instance->update(seconds_elapsed);
		pc->update(seconds_elapsed, scene, keystate, camera, numcam);

		scene->plane->update(seconds_elapsed);
	}

	//to navigate with the mouse fixed in the middle
	if (Game::instance->mouse_locked)
	{
		int center_x = (int)floor(Game::instance->window_width*0.5f);
		int center_y = (int)floor(Game::instance->window_height*0.5f);
		//center_x = center_y = 50;
		SDL_WarpMouseInWindow(Game::instance->window, center_x, center_y); //put the mouse back in the middle of the screen
																 //SDL_WarpMouseGlobal(center_x, center_y); //put the mouse back in the middle of the screen

		Game::instance->mouse_position.x = (float)center_x;
		Game::instance->mouse_position.y = (float)center_y;
	}


	angle += (float)seconds_elapsed * 10.0f;


	/***MOVIMIENTO AVIONES***/
	/*
	scene->p38->model.traslateLocal(0, 0, seconds_elapsed * 10 * speed);
	scene->p38a->model.traslateLocal(0, 0, seconds_elapsed * 10 * speed);
	scene->bomber->model.traslateLocal(0, 0, seconds_elapsed * 10 * speed);
	*/

}

void GameStage::onKeyPressed(SDL_KeyboardEvent event)
{
	switch (event.keysym.sym)
	{
	case SDLK_z: {numcam += 1; break; } //change camera player mode
	case SDLK_ESCAPE: exit(0); //ESC key, kill the app
	case SDLK_TAB: { control_camera = !control_camera; break;
		//case SDLK_SPACE: bm->shoot(camera->eye, Vector3(10,10,10), 1.00 ,5.00, scene->plane, 1);
	}
	}
}
void GameStage::onMouseButton(SDL_MouseButtonEvent event)
{

}