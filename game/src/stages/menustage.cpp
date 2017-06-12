#include "menustage.h"


MenuStage::MenuStage()
{

}
MenuStage::~MenuStage()
{

}
void MenuStage::init()
{

}
void MenuStage::render()
{
	//set the clear color (the background color)
	glClearColor(0, 0, 1, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}
void MenuStage::update(double dt)
{

}

void MenuStage::onKeyPressed(SDL_KeyboardEvent event)
{

}
void MenuStage::onMouseButton(SDL_MouseButtonEvent event)
{
	this->current->onChange("gamestage");
}