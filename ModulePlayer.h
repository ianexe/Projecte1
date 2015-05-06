#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2Qeue.h"
#include "ModuleCollision.h"

/*enum p1_states
{
	IDLE,
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

};*/


enum p1_states
{
	ST_UNKNOWN,

	ST_IDLE,
	ST_WALK_FORWARD,
	ST_WALK_BACKWARD,
	ST_JUMP_NEUTRAL,
	ST_JUMP_FORWARD,
	ST_JUMP_BACKWARD,
	ST_CROUCH,
	ST_PUNCH_STANDING_L,
	ST_PUNCH_STANDING_M,
	ST_PUNCH_STANDING_H,
	ST_KICK_STANDING_L,
	ST_KICK_STANDING_M,
	ST_KICK_STANDING_H,
	ST_PUNCH_NEUTRAL_JUMP,
	ST_PUNCH_FORWARD_JUMP,
	ST_PUNCH_BACKWARD_JUMP,
	ST_PUNCH_CROUCH,
	ST_HIT,
	ST_STUN
};

enum p1_inputs
{
	IN_LEFT_DOWN,
	IN_LEFT_UP,
	IN_RIGHT_DOWN,
	IN_RIGHT_UP,
	IN_LEFT_AND_RIGHT,
	IN_JUMP,
	IN_CROUCH_UP,
	IN_CROUCH_DOWN,
	IN_JUMP_AND_CROUCH,
	IN_X, // X = PUNCH
	IN_H, // H = HIT
	IN_JUMP_FINISH,
	IN_PUNCH_FINISH,
	IN_HIT_FINISH
};











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
	bool external_input(p2Qeue<p1_inputs>& inputs);
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