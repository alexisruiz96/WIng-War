#include "stage.h"


std::map<std::string, Stage*> s_Stages;


void Stage::onChange(const char* stagename)
{

	std::map<std::string, Stage*>::iterator it = s_Stages.find(stagename);
	if (it != s_Stages.end())
		current = it->second;
}