#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
//#include "p2Point.h"
//#include "ModuleCollision.h"
#include "States.h"
//#include "ModuleInput.h"
class ModulePlayer2 : public Module
{
public:
	ModulePlayer2(Application* app, bool start_enabled = true);
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();

	//State Machine methods
	p1_states process_fsm(p2Qeue<p1_inputs>& inputs);
	void internal_input(p2Qeue<p1_inputs>& inputs);

	//What it does when collides
	void OnCollision(Collider* c1, Collider* c2);
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
	unsigned int fallingFX;

	//State Machine variables
	p2Qeue<p1_inputs> inputs2;
	p1_states current_state;

	//Bools
	bool isOnLeft;

	bool isCrouching;
	bool isJumping;
	bool isFalling;
	//bool isAttacking;
	bool isPunching_L;
	bool isPunching_H;
	bool isKicking_L;
	bool isKicking_H;

	bool isHit;
	bool doDefense;
	//PNJ basics
	p2Point<int> position;
	unsigned int Health;
	float speed;

	//SDL_Rect detection;
	Collider* collider;
	Collider* c_defense;
	Collider* c_punch1;
	Collider* c_punch2;
	Collider* c_kick;
	Collider* c_kick2;


	
};