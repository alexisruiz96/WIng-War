#pragma once

#include "stage.h"


class FirstScreen : public Stage
{
public:
	static FirstScreen* instance;

	static FirstScreen* getInstance() {
		return instance;
	}
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
	bool idf;

	virtual void onKeyPressed(SDL_KeyboardEvent event);
	virtual void onMouseButton(SDL_MouseButtonEvent event);
};

