#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleUI : public Module
{
public:
	ModuleUI(Application* app, bool start_enabled = true);
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();
	
public:
	SDL_Texture* graphics;
	SDL_Rect lifebar;

	float x;
	float y;
};