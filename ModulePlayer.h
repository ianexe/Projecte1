#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics;
	Collider* collider;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation punch;
	Animation punch2;
	Animation kick;

	bool isOnLeft;

	bool isAttacking;

	bool doPunch;
	bool doPunch2;
	bool doKick;

	p2Point<float> position;
};