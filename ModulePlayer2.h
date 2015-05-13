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
	//Methods
	ModulePlayer2(Application* app, bool start_enabled = true);
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);
public:

	//Animation
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

	//State methods
	bool external_input(p2Qeue<p1_inputs>& inputs);
	void internal_input(p2Qeue<p1_inputs>& inputs);
	p1_states process_fsm(p2Qeue<p1_inputs>& inputs);
	//State Variables
	p2Qeue<p1_inputs> inputs;
	p1_states current_state;

	//Colliders
	Collider* collider;
	Collider* c_punch1;
	Collider* c_punch2;
	Collider* c_kick;
	//Pointer to current animation
	Animation* current_animation;
	
	//Variables
	bool isOnLeft;

	//Timers
	Uint32 jump_timer2;
	Uint32 punch_timer2;
	Uint32 hit_timer2;

	//Bools
	bool isAttacking;
	bool doPunch;
	bool doPunch2;
	bool doKick;

	//Character basics

	//TODO: Si no s'ajusta la velocitat, cambiar la posicio i la speed a float
	p2Point<int> position;
	unsigned int Health;
	int speed;
};