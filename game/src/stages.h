#pragma once

#include "includes.h"

class Stage
{
public:

	static Stage* current;

	static void changeStage(const char* name);

	virtual void init() {}
	virtual void render() {}
	virtual void update(double dt) {}

	virtual void onKeyPressed(SDL_KeyboardEvent event) {}
	virtual void onMouseButton(SDL_MouseButtonEvent event) {}

};

class MenuStage : public Stage
{
public:
	MenuStage(SDL_Window* window);

	SDL_Window* window;

	virtual void init();
	virtual void render();
	virtual void update(double dt);

	virtual void onKeyPressed(SDL_KeyboardEvent event);
	virtual void onMouseButton(SDL_MouseButtonEvent event);
};

class GameStage : public Stage
{
public:
	GameStage(SDL_Window* window);

	SDL_Window* window;

	virtual void init();
	virtual void render();
	virtual void update(double dt);

	virtual void onKeyPressed(SDL_KeyboardEvent event);
	virtual void onMouseButton(SDL_MouseButtonEvent event);
};

