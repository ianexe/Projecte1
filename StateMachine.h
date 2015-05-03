#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_
#include <stdio.h>
#include <string.h>
#include "p2Qeue.h"
#include "SDL\include\SDL.h"
/*
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )*/

#define JUMP_TIME 3000
#define PUNCH_TIME 1000
#define HIT_TIME 500

enum ryu_states
{
	ST_UNKNOWN,

	ST_IDLE,
	ST_WALK_FORWARD,
	ST_WALK_BACKWARD,
	ST_JUMP_NEUTRAL,
	ST_JUMP_FORWARD,
	ST_JUMP_BACKWARD,
	ST_CROUCH,
	ST_PUNCH_STANDING,
	ST_PUNCH_NEUTRAL_JUMP,
	ST_PUNCH_FORWARD_JUMP,
	ST_PUNCH_BACKWARD_JUMP,
	ST_PUNCH_CROUCH,
	ST_HIT
};

enum ryu_inputs
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
	IN_J, // J = HIT
	IN_JUMP_FINISH,
	IN_PUNCH_FINISH,
	IN_HIT_FINISH
};

Uint32 jump_timer = 0;
Uint32 punch_timer = 0;
Uint32 hit_timer = 0;

bool external_input(p2Qeue<ryu_inputs>& inputs)
{
	static bool left = false;
	static bool right = false;
	static bool down = false;
	static bool up = false;

	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				return false;
				break;
			case SDLK_DOWN:
				inputs.Push(IN_CROUCH_UP);
				down = false;
				break;
			case SDLK_UP:
				up = false;
				break;
			case SDLK_LEFT:
				inputs.Push(IN_LEFT_UP);
				left = false;
				break;
			case SDLK_RIGHT:
				inputs.Push(IN_RIGHT_UP);
				right = false;
				break;
			}
		}
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_SPACE:
				inputs.Push(IN_X);
				break;
			case SDLK_j:
				inputs.Push(IN_J);
				break;
			case SDLK_UP:
				up = true;
				break;
			case SDLK_DOWN:
				down = true;
				break;
			case SDLK_LEFT:
				left = true;
				break;
			case SDLK_RIGHT:
				right = true;
				break;
			}
		}
	}

	if (left && right)
		inputs.Push(IN_LEFT_AND_RIGHT);
	{
		if (left)
			inputs.Push(IN_LEFT_DOWN);
		if (right)
			inputs.Push(IN_RIGHT_DOWN);
	}

	if (up && down)
		inputs.Push(IN_JUMP_AND_CROUCH);
	else
	{
		if (down)
			inputs.Push(IN_CROUCH_DOWN);
		if (up)
			inputs.Push(IN_JUMP);
	}

	return true;
}

void internal_input(p2Qeue<ryu_inputs>& inputs)
{
	if (jump_timer > 0)
	{
		if (SDL_GetTicks() - jump_timer > JUMP_TIME)
		{
			inputs.Push(IN_JUMP_FINISH);
			jump_timer = 0;
		}
	}

	if (punch_timer > 0)
	{
		if (SDL_GetTicks() - punch_timer > PUNCH_TIME)
		{
			inputs.Push(IN_PUNCH_FINISH);
			punch_timer = 0;
		}
	}

	if (hit_timer > 0)
	{
		if (SDL_GetTicks() - hit_timer > HIT_TIME)
		{
			inputs.Push(IN_HIT_FINISH);
			punch_timer = 0;
		}
	}
}

ryu_states process_fsm(p2Qeue<ryu_inputs>& inputs)
{
	static ryu_states state = ST_IDLE;
	ryu_inputs last_input;

	while (inputs.Pop(last_input))
	{
		switch (state)
		{
		case ST_IDLE:
		{
			switch (last_input)
			{
			case IN_RIGHT_DOWN: state = ST_WALK_FORWARD; break;
			case IN_LEFT_DOWN: state = ST_WALK_BACKWARD; break;
			case IN_JUMP: state = ST_JUMP_NEUTRAL; jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			case IN_X: state = ST_PUNCH_STANDING; punch_timer = SDL_GetTicks();  break;
			case IN_J: state = ST_HIT; hit_timer = SDL_GetTicks();  break;
			}
		}
		break;

		case ST_HIT:
		{
			switch (last_input)
			{
			case IN_HIT_FINISH: state = ST_IDLE; break;
			}
		}
		break;


		case ST_WALK_FORWARD:
		{
			switch (last_input)
			{
			case IN_RIGHT_UP: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
			case IN_JUMP: state = ST_JUMP_FORWARD; jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			}
		}
		break;

		case ST_WALK_BACKWARD:
		{
			switch (last_input)
			{
			case IN_LEFT_UP: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
			case IN_JUMP: state = ST_JUMP_BACKWARD; jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			}
		}
		break;

		case ST_JUMP_NEUTRAL:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_X: state = ST_PUNCH_NEUTRAL_JUMP; punch_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_JUMP_FORWARD:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_X: state = ST_PUNCH_FORWARD_JUMP; punch_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_JUMP_BACKWARD:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_X: state = ST_PUNCH_BACKWARD_JUMP; punch_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_PUNCH_NEUTRAL_JUMP:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_PUNCH_FINISH: state = ST_JUMP_NEUTRAL; break;
			}
		}
		break;

		case ST_PUNCH_FORWARD_JUMP:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_PUNCH_FINISH: state = ST_JUMP_FORWARD; break;
			}
		}
		break;

		case ST_PUNCH_BACKWARD_JUMP:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_PUNCH_FINISH: state = ST_JUMP_BACKWARD; break;
			}
		}
		break;

		case ST_PUNCH_STANDING:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE; break;
			}
		}
		break;

		case ST_CROUCH:
		{
			switch (last_input)
			{
			case IN_X: state = ST_PUNCH_CROUCH; punch_timer = SDL_GetTicks(); break;
			case IN_CROUCH_UP: state = ST_IDLE; break;

			}
		}
		break;
		case ST_PUNCH_CROUCH:
		{
			switch (last_input)
			{

			case IN_PUNCH_FINISH: state = ST_IDLE; break;
			}
		}
		break;
		}
	}

	return state;
}

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* win;
	SDL_Renderer* renderer;
	SDL_CreateWindowAndRenderer(320, 240, 0, &win, &renderer);

	p2Qeue<ryu_inputs> inputs;
	ryu_states current_state = ST_UNKNOWN;
	printf("Listening for WASD + SPACE:\n");

	while (external_input(inputs))
	{

		internal_input(inputs);

		ryu_states state = process_fsm(inputs);

		if (state != current_state)
		{
			switch (state)
			{
			case ST_IDLE:
				printf("IDLE\n");
				break;
			case ST_HIT:
				printf("HIT\n");
				break;
			case ST_WALK_FORWARD:
				printf("FORWARD >>>\n");
				break;
			case ST_WALK_BACKWARD:
				printf("BACKWARD <<<\n");
				break;
			case ST_JUMP_NEUTRAL:
				printf("JUMPING NEUTRAL ^^^^\n");
				break;
			case ST_JUMP_FORWARD:
				printf("JUMPING FORWARD ^^>>\n");
				break;
			case ST_JUMP_BACKWARD:
				printf("JUMPING BACKWARD ^^<<\n");
				break;
			case ST_CROUCH:
				printf("CROUCHING ****\n");
				break;
			case ST_PUNCH_CROUCH:
				printf("PUNCH CROUCHING **++\n");
				break;
			case ST_PUNCH_STANDING:
				printf("PUNCH STANDING ++++\n");
				break;
			case ST_PUNCH_NEUTRAL_JUMP:
				printf("PUNCH JUMP NEUTRAL ^^++\n");
				break;
			case ST_PUNCH_FORWARD_JUMP:
				printf("PUNCH JUMP FORWARD ^>>+\n");
				break;
			case ST_PUNCH_BACKWARD_JUMP:
				printf("PUNCH JUMP BACKWARD ^<<+\n");
				break;
			}
		}
		current_state = state;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}

#endif