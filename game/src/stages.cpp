#include "stages.h"
#include "game.h"



MenuStage::MenuStage(SDL_Window* window)
{
	this->window = window;
}
void MenuStage::init() 
{
	
}
void MenuStage::render()
{
	//set the clear color (the background color)
	glClearColor(1, 1, 0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SDL_GL_SwapWindow(this->window);
}
void MenuStage::update(double dt)
{

}

void MenuStage::onKeyPressed(SDL_KeyboardEvent event)
{

}
void MenuStage::onMouseButton(SDL_MouseButtonEvent event)
{
	Stage::current = new GameStage(this->window);
}

GameStage::GameStage(SDL_Window* window)
{
	this->window = window;
}

void GameStage::init()
{
	Game::instance->init();
}

void GameStage::render()
{
	Game::instance->render();
}

void GameStage::update(double time_elapsed)
{
	Game::instance->update(time_elapsed);
}

void GameStage::onKeyPressed(SDL_KeyboardEvent event)
{

}
void GameStage::onMouseButton(SDL_MouseButtonEvent event)
{

}