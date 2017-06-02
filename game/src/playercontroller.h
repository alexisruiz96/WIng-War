#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "includes.h"


class PlayerController
{
public:
	PlayerController();
	~PlayerController();


	void render(void);
	void update(double seconds_elapsed, int numc);

};

#endif 