#include "endstage.h"
#include "gamestage.h"


EndStage::EndStage()
{
}


EndStage::~EndStage()
{
}

void EndStage::init()
{

}

void EndStage::render()
{
	glClearColor(0, 1, 0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void EndStage::update(float seconds_elapsed)
{

}

void EndStage::onKeyPressed(SDL_KeyboardEvent event)
{

}

void EndStage::onMouseButton(SDL_MouseButtonEvent event)
{
	GameStage::instance->repeat = true;
	Stage::instance->current->onChange("menustate");
	
}