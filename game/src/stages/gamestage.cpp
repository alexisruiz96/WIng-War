#include "gamestage.h"
#include "../entitycollider.h"
#include "endstage.h"
#include "../bass.h"
float angle = 0;
Scene* scene = NULL;
Shader * shader = NULL;

bool control_camera = false;
int cam_position = 0;
int numcam = 0;

const Uint8* keystate = NULL;
PlayerController* pc = NULL;
GameStage* GameStage::instance = NULL;



GameStage::GameStage()
{
	instance = this;
	hSample6 = NULL;
	hSampleChannel6 = NULL;
}

void GameStage::init()
{
	ps = false;
	

	game = Game::getInstance();
	//game->camera->lookAt(Vector3(0.f, 25.f, 25.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f)); //position the camera and point to 0,0,0
	//game->camera->setPerspective(70.f, Game::instance->window_width / (float)Game::instance->window_height, 0.1f, 100000.f); //set the projection, we want to be perspective
	//create our camera
	game->camera = new Camera();
	game->camera->lookAt(Vector3(0, 750, 0), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f)); //position the camera
	game->camera->setPerspective(70.f, Game::instance->window_width / (float)Game::instance->window_height, 0.1f, 100000.f); //set the projection, we want to be perspective
			//std::cout << scene->plane->model << std::endl;
			//test = new EntityMesh();
		   //test->config("data/meshes/spitfire/spitfire_color_spec.tga", "data/meshes/spitfire/spitfire.ASE");
	scene = new Scene();
	scene->createScene();

	BulletManager::instance = new BulletManager();

	pc = new PlayerController();

	EndStage::instance->succes = false;

	BASS_Init(1, 44100, 0, 0, NULL);
	//Cargamos un sample (memoria, filename, offset, length, max, flags)
	hSample6 = BASS_SampleLoad(false, "data/sounds/planesound.wav", 0, 0, 3, 0);
	//Creamos un canal para el sample
	hSampleChannel6 = BASS_SampleGetChannel(hSample6, false);

}
void GameStage::secondinit()
{

	game = Game::getInstance();

	game->camera = new Camera();
	game->camera->lookAt(Vector3(0, 750, 0), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f)); //position the camera
	game->camera->setPerspective(70.f, Game::instance->window_width / (float)Game::instance->window_height, 0.1f, 100000.f); //set the projection, we want to be perspective
	//std::cout << scene->plane->model << std::endl;
	//test = new EntityMesh();
	//test->config("data/meshes/spitfire/spitfire_color_spec.tga", "data/meshes/spitfire/spitfire.ASE");
	scene = new Scene();
	scene->createScene();

	BulletManager::instance = new BulletManager();

	pc = new PlayerController();

	EndStage::instance->succes = false;

	BASS_Init(1, 44100, 0, 0, NULL);
	//Cargamos un sample (memoria, filename, offset, length, max, flags)
	hSample6 = BASS_SampleLoad(false, "data/sounds/planesound.wav", 0, 0, 3, 0);
	//Creamos un canal para el sample
	hSampleChannel6 = BASS_SampleGetChannel(hSample6, false);
}

void GameStage::render()
{

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//set the clear color (the background color)
	glClearColor(0.15, 0.30, 0.35, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Put the camera matrices on the stack of OpenGL (only for fixed rendering)
	game->camera->set();

	//Draw out world
	//drawGrid(500); //background grid

	glDisable(GL_DEPTH_TEST);
	scene->cielo->model.setIdentity();
	scene->cielo->model.traslate(game->camera->eye.x, game->camera->eye.y, game->camera->eye.z);
	scene->cielo->render(shader);
	glEnable(GL_DEPTH_TEST);

	
	
	/*scene->water->model.setIdentity();
	scene->water->model.traslate(game->camera->eye.x, 0, game->camera->eye.z);
	scene->water->render(game->camera, shader);*/


	scene->root->render(shader);

	if (ps)
		BASS_ChannelPlay(hSampleChannel6, false);
	//camera pos
	//std::cout << camera->eye.x << " - " << camera->eye.y << " - " << camera->eye.z << std::endl; 
	
	BulletManager::instance->render();

	if (pc->useGUI)
		renderGUI();

	std::stringstream vida;
	vida << "HP : " << scene->plane->hp << "%";
	drawText(game->window_width * 0.1, game->window_height * 0.9, vida.str(), Vector3(1, 0.01*scene->plane->hp, 0.01*scene->plane->hp), 2);



	std::stringstream coord;
	coord << "pos : (" << game->camera->eye.x << "," << game->camera->eye.y << "," << game->camera->eye.z << ")";
	drawText(game->window_width * 0.7, game->window_height * 0.9, coord.str(), Vector3(1, 1, 1), 2);


	std::stringstream vidabarco;
	vidabarco << "Enemy boat : " << scene->barco->hp << "%";
	drawText(game->window_width * 0.1, game->window_height * 0.85, vidabarco.str(), Vector3(1, 0.005*scene->barco->hp, 0.005*scene->barco->hp), 2);

}

void GameStage::renderGUI()
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND); //transparencia
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	Camera cam2D;
	cam2D.setOrthographic(0, Game::instance->window_width, Game::instance->window_height, 0, -1, 1);
	cam2D.set();
	
	Mesh quad;
	Texture* cross = Texture::Load("data/meshes/crosshair.TGA");
	cross->bind();
	quad.createQuad(Game::instance->window_width*0.5, Game::instance->window_height*0.5, 50, 50);
	quad.render(GL_TRIANGLES);
	cross->unbind();
	
}

void GameStage::update(double seconds_elapsed)
{
	keystate = Game::instance->keystate;
	float speed = seconds_elapsed * 100; //the speed is defined by the seconds_elapsed so it goes constant

										 //mouse input to rotate the cam
	if ((Game::instance->mouse_state & SDL_BUTTON_LEFT) || Game::instance->mouse_locked) //is left button pressed?
	{
		game->camera->rotate(Game::instance->mouse_delta.x * 0.005f, Vector3(0.0f, -1.0f, 0.0f));
		game->camera->rotate(Game::instance->mouse_delta.y * 0.005f, game->camera->getLocalVector(Vector3(-1.0f, 0.0f, 0.0f)));
	}

	//async input to move the camera around
	if (control_camera)
	{
		if (keystate[SDL_SCANCODE_LSHIFT]) speed *= 100; //move faster with left shift
		if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP]) game->camera->move(Vector3(0.0f, 0.0f, 1.0f) * speed);
		if (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN]) game->camera->move(Vector3(0.0f, 0.0f, -1.0f) * speed);
		if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT]) game->camera->move(Vector3(1.0f, 0.0f, 0.0f) * speed);
		if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT]) game->camera->move(Vector3(-1.0f, 0.0f, 0.0f) * speed);
	}
	else
	{
		//Vector3 lastpos = scene->plane->model * Vector3(1, 1, 1);

		BulletManager::instance->update(seconds_elapsed);
		pc->update(seconds_elapsed, numcam);

		//scene->plane->update(seconds_elapsed);

		
	}

	scene->plane->model.traslateLocal(0, 0, seconds_elapsed * 10);

	scene->root->update(seconds_elapsed);
	/*scene->plane->update(seconds_elapsed);
	scene->p38->update(seconds_elapsed);
	scene->p38a->update(seconds_elapsed);
	scene->bomber->update(seconds_elapsed);
	scene->barco->update(seconds_elapsed);*/

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
	case SDLK_p: {scene->plane->hp = scene->plane->hp - 5;}
	}
}
void GameStage::onMouseButton(SDL_MouseButtonEvent event)
{

}
