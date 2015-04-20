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
	//Methods
	ModuleIntro(Application* app, bool start_enabled = true);
	~ModuleIntro(){}

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	//Variables
	SDL_Texture* graphics;
	SDL_Rect scroll;
	//Animation punchFace;
	bool isEnd;


};
