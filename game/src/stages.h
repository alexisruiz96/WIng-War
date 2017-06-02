#pragma once

#include "includes.h"
#include <map>
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
#include "bulletmanager.h"
#include "camera.h"
#include "playercontroller.h"
#include "game.h"

class PlayerController;
class Stage
{
public:

	static std::map<std::string, Stage*> s_Stages;
	static Stage* current;

	static void onChange(const char* stagename);

	virtual void init() {}
	virtual void render() {}
	virtual void update(double dt) {}

	virtual void onKeyPressed(SDL_KeyboardEvent event) {}
	virtual void onMouseButton(SDL_MouseButtonEvent event) {}

};

class MenuStage : public Stage
{
public:
	MenuStage();


	virtual void init();
	virtual void render();
	virtual void update(double dt);

	virtual void onKeyPressed(SDL_KeyboardEvent event);
	virtual void onMouseButton(SDL_MouseButtonEvent event);
};

class GameStage : public Stage
{
public:
	static GameStage* instance;

	static GameStage* getInstance() {
		return instance;
	}
	GameStage();

	const Uint8* keystate;

	Camera* camera;
	PlayerController* pc;

	virtual void init();
	virtual void render();
	virtual void renderGUI();
	virtual void update(double dt);

	virtual void onKeyPressed(SDL_KeyboardEvent event);
	virtual void onMouseButton(SDL_MouseButtonEvent event);
};

