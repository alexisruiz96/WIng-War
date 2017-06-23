#include "stage.h"


class EndStage : public Stage
{
public:
	EndStage();
	virtual ~EndStage();

	virtual void init();
	virtual void render();
	virtual void update(float dt);

	Texture* text;
	Camera camfscreen;
	Game* game;
	Mesh quadforstart;

	virtual void onKeyPressed(SDL_KeyboardEvent event);
	virtual void onMouseButton(SDL_MouseButtonEvent event);
};