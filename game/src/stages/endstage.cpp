#include "endstage.h"
#include "gamestage.h"
#include "../entitycollider.h"
#include "../bass.h"
#include "menustage.h"

EndStage* EndStage::instance = NULL;
SDL_Joystick *joye = NULL;
//El handler para un sample
HSAMPLE hSample4, hSample5;

//El handler para un canal
HCHANNEL hSampleChannel4, hSampleChannel5;
EndStage::EndStage()
{
	instance = this;

	if (SDL_NumJoysticks()> 0) {
		joye = SDL_JoystickOpen(0);
	}
}


EndStage::~EndStage()
{
}

void EndStage::init()
{
	textgameover = Texture::Load("data/menu/gameover.tga");
	textsucces = Texture::Load("data/menu/missucces.tga");
	game = Game::getInstance();


	quadforstart.createQuad(game->window_width*0.5, game->window_height*0.5, game->window_width, game->window_height, true);
	camfscreen.setOrthographic(0.0, game->window_width, game->window_height, 0.0, -1.0, 1.0);

	BASS_Init(1, 44100, 0, 0, NULL);
	//Cargamos un sample (memoria, filename, offset, length, max, flags)
	hSample4 = BASS_SampleLoad(false, "data/sounds/succes.wav", 0, 0, 3, 0);
	hSample5 = BASS_SampleLoad(false, "data/sounds/gameover.wav", 0, 0, 3, 0);
	//Creamos un canal para el sample
	hSampleChannel4 = BASS_SampleGetChannel(hSample4, false);
	hSampleChannel5 = BASS_SampleGetChannel(hSample5, false);

	go = false;
	ms = false;

}

void EndStage::render()
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glClearColor(0, 1, 0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	camfscreen.set();
	glColor4f(1.f, 1.f, 1.f, 1.f);

	if (!instance->succes)
	{
		if (!go)
			BASS_ChannelPlay(hSampleChannel5, false);
		go = true;
		textgameover->bind();
		quadforstart.render(GL_TRIANGLES);
		textgameover->unbind();
	}
	else 
	{
		if(!ms)
			BASS_ChannelPlay(hSampleChannel4, false);
		ms = true;
		textsucces->bind();
		quadforstart.render(GL_TRIANGLES);
		textsucces->unbind();
	}

	std::stringstream back;
	back << "ESC / (BACK) - BACK TO MENU";
	drawText(game->window_width * 0.35, game->window_height * 0.90, back.str(), Vector3(1, 1, 1), 3);
}

void EndStage::update(double seconds_elapsed)
{

	if (joye) {
		JoystickState jst = getJoystickState(joye);

		if (jst.button[BACK_BUTTON]) {
			GameStage::instance->repeat = true;
			MenuStage::instance->secondInit();
			Stage::instance->current->onChange("menustate");
		}
	}
}

void EndStage::onKeyPressed(SDL_KeyboardEvent event)
{
	GameStage::instance->repeat = true;
	MenuStage::instance->secondInit();

	Stage::instance->current->onChange("menustate");
}

void EndStage::onMouseButton(SDL_MouseButtonEvent event)
{
	GameStage::instance->repeat = true;
	MenuStage::instance->secondInit();

	Stage::instance->current->onChange("menustate");
	
}