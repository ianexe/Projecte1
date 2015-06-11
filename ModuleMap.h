#pragma once
#include "Module.h"
#include "Application.h"
#include "Globals.h"



class ModuleMap : public Module
{
public:
	//Methods
	ModuleMap(Application* app, bool start_enabled = true);
	~ModuleMap(){}

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	//Variables
	SDL_Texture* map_selection;
	SDL_Texture* versus_image;

	Animation countdown;

	bool music_on;
	bool map;

	unsigned int music_versus;

	SDL_Rect scroll;


};
