#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleRender : public Module
{
public:
	ModuleRender(Application* app, bool start_enabled = true);
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed = 1.0f, bool mirror = true);
	void setScreenBorders();
public:
	SDL_Renderer* renderer;
	SDL_Rect camera;
	SDL_Rect displacement;
	int distance;
	int distance2;
	int centerCameraX;
};