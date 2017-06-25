#include "endstage.h"
#include "gamestage.h"
#include "../entitycollider.h"
#include "../bass.h"
#include "menustage.h"

EndStage* EndStage::instance = NULL;

//El handler para un sample
HSAMPLE hSample4, hSample5;

//El handler para un canal
HCHANNEL hSampleChannel4, hSampleChannel5;
EndStage::EndStage()
{
	instance = this;
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
	std::cout << "perknovaputoaki" << std::endl;
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glClearColor(0, 1, 0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	std::cout << "kelorraaa" << std::endl;
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
	std::cout << "si homa" << std::endl;
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

	MenuStage::instance->secondInit();

	Stage::instance->current->onChange("menustate");
	
}