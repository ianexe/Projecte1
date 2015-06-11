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
	Animation jumpforward;
	Animation jumpforwardfalling;
	Animation jumpbackward;
	Animation jumpbackwardfalling;
	Animation block;
	Animation crouch;
	Animation crouchidle;
	Animation punch;
	Animation punch2;
	Animation kick;
	Animation kick2;
	Animation crouchpunch;
	Animation crouchkick;
	Animation jumppunch;
	Animation jumpkick;
	Animation hadoukenmove;
	unsigned int normalFX;
	unsigned int strongFX;
	unsigned int fallingFX;


	//SDL_Rect detection;
	Collider* collider;
	Collider* c_defense;
	Collider* c_punch1;
	Collider* c_punch2;
	Collider* c_kick;
	Collider* c_kick2;
	//State Variables
	p1_states current_state;
	p2Qeue<p1_inputs> inputs;
	//Timers
	
	

	//Variables
	
	//bools
	bool isOnLeft;

	bool isCrouching;
	bool isJumping;
	bool isFalling;
	bool isAttacking;
	bool isPunching_L;
	bool isPunching_H;
	bool isKicking_L;
	bool isKicking_H;

	bool isJumpPunching;
	bool isCrouchPunching;
	bool isJumpKicking;
	bool isCrouchKicking;

	bool isHit;
	
	bool doDefense;
	//Character basics
	p2Point<int> position;
	unsigned int Health;
	float speed;

};