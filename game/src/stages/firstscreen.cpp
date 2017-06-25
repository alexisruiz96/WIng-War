#include "firstscreen.h"

Vector2 screen;

FirstScreen::FirstScreen()
{
	
}


FirstScreen::~FirstScreen()
{
}

void FirstScreen::init() {

	game = Game::getInstance();

	text = Texture::Load("data/menu/firstscreen.tga");


	camera2D.setOrthographic(0.0, game->window_width, game->window_height, 0.0, -1.0, 1.0);
	quadMenu.createQuad(game->window_width*0.5, game->window_height*0.5, game->window_width, game->window_height, true);


}

void FirstScreen::render() {

	glDisable(GL_CULL_FACE); //render both sides of every triangle
	glDisable(GL_DEPTH_TEST); //check the occlusions using the Z buffer
	glDisable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(1, 0, 0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera2D.set();
	glColor4f(1.f, 1.f, 1.f, 1.f);

	text->bind();
	quadMenu.render(GL_TRIANGLES);
	text->unbind();


}

void FirstScreen::update(double dt) {

}

void FirstScreen::onKeyPressed(SDL_KeyboardEvent event) {

}
void FirstScreen::onMouseButton(SDL_MouseButtonEvent event) {
	Stage::instance->current->onChange("menustate");
	
}