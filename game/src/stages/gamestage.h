#pragma once
#include "stage.h"

class GameStage : public Stage
{
public:
	static GameStage* instance;

	static GameStage* getInstance() {
		return instance;
	}
	GameStage();

	const Uint8* keystate;
	Game* game;
	PlayerController* pc;
	bool repeat;

	virtual void init();
	virtual void render();
	virtual void renderGUI();
	virtual void update(double dt);

	virtual void onKeyPressed(SDL_KeyboardEvent event);
	virtual void onMouseButton(SDL_MouseButtonEvent event);
	virtual void secondinit();
};

