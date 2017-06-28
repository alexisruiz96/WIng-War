#pragma once

#include "stage.h"

class ControlStage : public Stage
{
public:
	static ControlStage* instance;

	static ControlStage* getInstance() {
		return instance;
	}

	ControlStage();
	virtual ~ControlStage();


	virtual void init();
	virtual void render();
	virtual void update(double dt);

	Texture* text;
	Camera camera2D;
	Game* game;
	Mesh quadMenu;

	virtual void onKeyPressed(SDL_KeyboardEvent event);
	virtual void onMouseButton(SDL_MouseButtonEvent event);
};

