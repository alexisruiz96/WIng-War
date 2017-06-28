#include "firstscreen.h"
#include "gamestage.h"
#include "../bass.h"
#include "../utils.h"
Vector2 screen;

SDL_Joystick *joyf = NULL;
FirstScreen* FirstScreen::instance = NULL;
FirstScreen::FirstScreen()
{
	instance = this;
	idk = true;
	idf = false;

	if (SDL_NumJoysticks()> 0) {
		joyf = SDL_JoystickOpen(0);
	}
}


FirstScreen::~FirstScreen()
{
}

void FirstScreen::init() {

	//if (idk) {
		GameStage::instance->render();
	//	std::cout << "asdasd";
	//	idk = false;
	//}
	//if (!idk && !idf)
	//{

		EntityCollider::deleteAllColliders();
		Entity::toDestroy.push_back(Scene::instance->root);
		Entity::toDestroy.push_back(Scene::instance->cielo);
		Scene::instance->plane->deleteEntity();

		GameStage::instance->secondinit();
		//idf = true;
	//}

	

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
	
	
	if (joyf) {
		JoystickState jst = getJoystickState(joyf);
		if (jst.button[START_BUTTON]) {

			Stage::instance->current->onChange("menustate");
		}
	}
}

void FirstScreen::onKeyPressed(SDL_KeyboardEvent event) {
	
	
	
}
void FirstScreen::onMouseButton(SDL_MouseButtonEvent event) {

	//GameStage::instance->ps = true;
	Stage::instance->current->onChange("menustate");
	
}