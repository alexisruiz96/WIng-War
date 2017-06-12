#include "firstscreen.h"



FirstScreen::FirstScreen()
{
}


FirstScreen::~FirstScreen()
{
}

void FirstScreen::init() {

	text = Texture::Load("data/menu/firstscreen.tga");
	game = Game::getInstance();

	quadforstart.createQuad(game->window_width / 2, game->window_height / 2, game->window_width, game->window_height, true);
	camfscreen.setOrthographic(0.0, game->window_width, game->window_height, 0.0, -1.0, 1.0);
}

void FirstScreen::render() {


	text->bind();
	quadforstart.render(GL_TRIANGLES);
	text->unbind();
}

void FirstScreen::update(double dt) {

}

void FirstScreen::onKeyPressed(SDL_KeyboardEvent event) {

}
void FirstScreen::onMouseButton(SDL_MouseButtonEvent event) {
	this->current->onChange("menustate");
}