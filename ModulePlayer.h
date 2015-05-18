#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"
#include "States.h"





/*
p1_states states = IDLE;
switch (states)
{
case IDLE:
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
	{
		state = WALK_R;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		state = WALK_L;
	}
	break;
	WALK_R,
	WALK_L,
	CROUCH,
	JUMP,
	JUMP_L,
	JUMP_R,
	PUNCH_L,
	PUNCH_M,
	PUNCH_H,
	KICK_L,
	KICK_M,
	KICK_H,
	HIT_L,
	STUN,
}
*/


class ModulePlayer : public Module
{
public:
	//Methods
	ModulePlayer(Application* app, bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);
	//State methods
	void internal_input(p2Qeue<p1_inputs>& inputs);
	p1_states process_fsm(p2Qeue<p1_inputs>& inputs);

public:
	
	SDL_Texture* graphics;
	//Animations

	Animation idle;
	Animation forward;
	Animation backward;
	Animation punch;
	Animation punch2;
	Animation kick;
	SDL_Rect atac;
	SDL_Rect defense;

	//Pointer to current animation
	Animation* current_animation;

	//SDL_Rect detection;
	Collider* collider;
	Collider* c_punch1;
	Collider* c_punch2;
	Collider* c_kick;

	//State Variables
	p2Qeue<p1_inputs> inputs;
	p1_states current_state;
	
	//Variables
	//bools
	bool isOnLeft = false;

	bool isAttacking = false;

	bool doPunch;
	bool doPunch2;
	bool doKick;

	//Timers
	Uint32 jump_timer;
	Uint32 punch_timer;
	Uint32 hit_timer;

	//Character basics
	p2Point<int> position;
	unsigned int Health;
	float speed;


};