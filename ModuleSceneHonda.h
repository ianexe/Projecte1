#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleSceneHonda : public Module
{
public:
	ModuleSceneHonda(Application* app, bool start_enabled = true);
	~ModuleSceneHonda();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics;
	SDL_Rect ground;
	SDL_Rect roof;
	SDL_Rect foreground;
	SDL_Rect background;
	Animation water;
};