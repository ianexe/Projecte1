#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"
#include "States.h"
class ModulePlayer2 : public Module
{
public:
	ModulePlayer2(Application* app, bool start_enabled = true);
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();

	//State Machine methods
	player_states process_fsm(p2Qeue<p2_inputs>& inputs);
	void internal_input(p2Qeue<p2_inputs>& inputs);

	//What it does when collides
	void OnCollision(Collider* c1, Collider* c2);
public:

	//Pointer to current animation
	Animation* current_animation;

	//Colliders
	Collider* collider;
	Collider* c_punch1;
	Collider* c_punch2;
	Collider* c_kick;

	//Timers
	Uint32 jump_timer;
	Uint32 punch_timer;
	Uint32 hit_timer;

	//State Machine variables
	p2Qeue<p2_inputs> inputs2;
	player_states current_state;

	//Not so evil bools
	bool isOnLeft;
	bool isAttacking;

	//Evil bools
	bool doPunch;
	bool doPunch2;
	bool doKick;

	//PNJ basics
	p2Point<int> position;
	unsigned int Health;

	//Animations
	SDL_Texture* graphics;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation punch;
	Animation punch2;
	Animation kick;
	SDL_Rect atac;
	SDL_Rect defense;
	SDL_Rect detection;
};