#pragma once


class Controller
{
public:
	Controller();
	virtual ~Controller();

	void update(double seconds_elapsed);
};

