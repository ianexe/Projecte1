#pragma once
#include "Module.h"
#include "Animation.h"
#include "States.h"
//#include "ModuleInput.h"
//#include "Globals.h"
//#include "p2Point.h"
//#include "ModuleCollision.h"


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


	//Pointer to current animation
	Animation* current_animation;

	SDL_Rect shadow;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation jump;
	Animation jumpfalling;
	Animation block;
	Animation crouch;
	Animation crouchidle;
	Animation punch;
	Animation punch2;
	Animation kick;
	Animation kick2;
	unsigned int normalFX;
	unsigned int strongFX;


	//SDL_Rect detection;
	Collider* collider;
	Collider* c_punch1;
	Collider* c_punch2;
	Collider* c_kick;

	//State Variables
	p1_states current_state;
	p2Qeue<p1_inputs> inputs;
	//Timers
	
	Uint32 punch_timer_l;
	Uint32 punch_timer_h;
	Uint32 kick_timer_l;

	Uint32 hit_timer;

	//Variables
	
	//bools
	bool isOnLeft;
	bool isJumping;
	bool isFalling;
	bool isAttacking;

	/*bool doPunch;s
	bool doPunch2;
	bool doKick;
	bool doKick2;
	*/

	bool isCrouching;

	//Character basics
	p2Point<int> position;
	unsigned int Health;
	float speed;

};