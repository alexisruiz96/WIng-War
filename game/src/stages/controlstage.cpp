#include "controlstage.h"
#include "../game.h"
#include "../utils.h"

ControlStage* ControlStage::instance = NULL;
SDL_Joystick *joyc = NULL;

ControlStage::ControlStage()
{
	instance = this;

	if (SDL_NumJoysticks()> 0) {
		joyc = SDL_JoystickOpen(0);
	}
}


ControlStage::~ControlStage()
{
}


void ControlStage::init() {


	game = Game::getInstance();

	text = Texture::Load("data/menu/controls.tga");


	camera2D.setOrthographic(0.0, game->window_width, game->window_height, 0.0, -1.0, 1.0);
	quadMenu.createQuad(game->window_width*0.5, game->window_height*0.5, game->window_width, game->window_height, true);


}

void ControlStage::render() {
	
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

void ControlStage::update(double dt) {
	if (joyc) {
		JoystickState jst = getJoystickState(joyc);

		if (jst.button[BACK_BUTTON]) {
			Stage::instance->current->onChange("menustate");
		}
	}

}

void ControlStage::onKeyPressed(SDL_KeyboardEvent event) {

	switch (event.keysym.sym)
	{
		case SDLK_ESCAPE:{ Stage::instance->current->onChange("menustate"); break;} //ESC key, kill the app
	}




}
void ControlStage::onMouseButton(SDL_MouseButtonEvent event) {



}