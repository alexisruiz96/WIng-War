#pragma once

#include "stage.h"


class FirstScreen : public Stage
{
public:
	FirstScreen();
	virtual ~FirstScreen();

	virtual void init();
	virtual void render();
	virtual void update(double dt);

	Texture* text;
	Camera camera2D;
	Game* game;
	Mesh quadMenu;
	bool idk;

	virtual void onKeyPressed(SDL_KeyboardEvent event);
	virtual void onMouseButton(SDL_MouseButtonEvent event);
};

