#pragma once
#include "Module.h"
#include "Globals.h"


//Scroll
//Input
//Select stage?
//Que el joc torni a la intro quan mors!!!
//Que et moris!!
class ModuleIntro : public Module
{
public:
	ModuleIntro(Application* app, bool start_enabled = true);
	~ModuleIntro();

	bool Init();

	update_status Update();

	bool CleanUp();
};
