#include "menustage.h"
#include "../bass.h"

//El handler para un sample
HSAMPLE hSample2;

//El handler para un canal
HCHANNEL hSampleChannel2;
bool sound;
MenuStage::MenuStage()
{

}
MenuStage::~MenuStage()
{

}
void MenuStage::init()
{

	BASS_Init(1, 44100, 0, 0, NULL);
	//Cargamos un sample (memoria, filename, offset, length, max, flags)
	hSample2 = BASS_SampleLoad(false, "data/sounds/musicmenu.wav", 0, 0, 3, 0);
	//Creamos un canal para el sample
	hSampleChannel2 = BASS_SampleGetChannel(hSample2, false);
	
	sound = false;
	
	
}
void MenuStage::render()
{
	if (sound == false) {
		BASS_ChannelPlay(hSampleChannel2, true);
		sound = true;
	}
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
	BASS_ChannelStop(hSampleChannel2);
	this->current->onChange("gamestage");
}