#pragma once
#include "Module.h"
#include "Globals.h"


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
	SDL_Texture* intro_animation;
	SDL_Rect scroll;
	Animation intro;
	Animation insert_coin;

	//Animation punchFace;
	bool isEnd;


};
