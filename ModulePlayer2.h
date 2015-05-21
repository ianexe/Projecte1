#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

class ModulePlayer2 : public Module
{
public:
	//Methods
	ModulePlayer2(Application* app, bool start_enabled = true);
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);
public:

	SDL_Texture* graphics;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation punch;
	Animation punch2;
	Animation kick;

	Collider* collider;
	Collider* c_defense;
	Collider* c_punch1;
	Collider* c_punch2;
	Collider* c_kick;

	//Variables
	bool isOnLeft;

	bool isAttacking;

	bool doDefense;
	bool doPunch;
	bool doPunch2;
	bool doKick;
	bool doKick2;

	p2Point<float> position;
	unsigned int Health;
};