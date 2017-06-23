#pragma once
#include "stage.h"
class MenuStage : public Stage
{
public:

	static MenuStage* instance;

	static MenuStage* getInstance() {
		return instance;
	}
	MenuStage();
	virtual ~MenuStage();

	virtual void init();
	virtual void render();
	virtual void update(double dt);

	virtual void onKeyPressed(SDL_KeyboardEvent event);
	virtual void onMouseButton(SDL_MouseButtonEvent event);
};

