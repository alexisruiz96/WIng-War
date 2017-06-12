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
	Camera camfscreen;
	Game* game;
	Mesh quadforstart;

	virtual void onKeyPressed(SDL_KeyboardEvent event);
	virtual void onMouseButton(SDL_MouseButtonEvent event);
};

