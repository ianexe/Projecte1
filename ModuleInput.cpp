#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"

#define MAX_KEYS 300

ModuleInput::ModuleInput(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	keyboard = new KEY_STATE[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KEY_STATE)* MAX_KEYS);
}

// Destructor
ModuleInput::~ModuleInput()
{
	delete keyboard;
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}



bool ModuleInput::external_input(p2Qeue<p1_inputs>& inputs)
{
	//Player1
	static bool left = false;
	static bool right = false;
	static bool down = false;
	static bool up = false;
	static bool punch_l = false;
	static bool hit = false;
	//Player2
	static bool left_2 = false;
	static bool right_2 = false;
	static bool down_2 = false;
	static bool up_2 = false;
	static bool punch_l_2 = false;
	static bool hit_2 = false;
	SDL_Event event;

	if (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			/*case SDLK_ESCAPE:
				return false;
				break;*/
			//Player 1
			case SDLK_s:
				inputs.Push(_2_IN_CROUCH_UP);
				down = false;
				break;
			case SDLK_q:
				punch_l = false;
				break;
			case SDLK_w:
				up = false;
				break;
			case SDLK_a:
				inputs.Push(_2_IN_LEFT_UP);
				left = false;
				break;
			case SDLK_d:
				inputs.Push(_2_IN_RIGHT_UP);
				right = false;
				break;

				//Player2
			case SDLK_DOWN:
				inputs.Push(IN_CROUCH_UP);
				down = false;
				break;
			case SDLK_KP_1:
				punch_l = false;
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
			//Player 
			case SDLK_q:
				punch_l = true;
				break;
			case SDLK_h:
				hit = true;
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
			//Player 2
			case SDLK_KP_1:
				punch_l = true;
				break;
			case SDLK_KP_5:
				hit_2 = true;
				break;
			case SDLK_w:
				up = true;
				break;
			case SDLK_s:
				down = true;
				break;
			case SDLK_a:
				left = true;
				break;
			case SDLK_d:
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
	if (punch_l)
	{
		inputs.Push(IN_X);
	}
	return true;
}
/*
void ModuleInput::internal_input(p2Qeue<p1_inputs>& inputs2)
{
	if (jump_timer > 0)
	{
		if (SDL_GetTicks() - jump_timer > JUMP_TIME)
		{
			inputs2.Push(IN_JUMP_FINISH);
			jump_timer = 0;
		}
	}

	if (punch_timer > 0)
	{
		if (SDL_GetTicks() - punch_timer > PUNCH_TIME)
			//	if(current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			inputs2.Push(IN_PUNCH_FINISH);
			punch_timer = 0;
		}
	}

	if (hit_timer > 0)
	{
		if (SDL_GetTicks() - hit_timer > HIT_TIME)
		{
			inputs2.Push(IN_HIT_FINISH);
			punch_timer = 0;
		}
	}
}
*/



// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	if (keyboard[SDL_SCANCODE_ESCAPE] == KEY_UP)
		return UPDATE_STOP;

	SDL_GetMouseState(&mouse_x, &mouse_y);
	mouse_x /= SCREEN_SIZE;
	mouse_y /= SCREEN_SIZE;

	return UPDATE_CONTINUE;
}
// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}