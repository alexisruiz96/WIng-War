#include "stage.h"


class EndStage : public Stage
{
public:
	static EndStage* instance;

	static EndStage* getInstance() {
		return instance;
	}
	EndStage();
	virtual ~EndStage();
	virtual void init();
	virtual void render();
	virtual void update(float dt);

	bool succes;
	bool go;
	bool ms;
	Texture* textgameover;
	Texture* textsucces;
	Camera camfscreen;
	Game* game;
	Mesh quadforstart;

	virtual void onKeyPressed(SDL_KeyboardEvent event);
	virtual void onMouseButton(SDL_MouseButtonEvent event);
};