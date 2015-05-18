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



bool ModuleInput::external_input(p2Qeue<p1_inputs>& inputs2)
{
	static bool left = false;
	static bool right = false;
	static bool down = false;
	static bool up = false;
	static bool punch_l = false;

	SDL_Event event2;

	if (SDL_PollEvent(&event2) != 0)
	{
		if (event2.type == SDL_KEYUP && event2.key.repeat == 0)
		{
			switch (event2.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				return false;
				break;
			case SDLK_DOWN:
				inputs2.Push(IN_CROUCH_UP);
				down = false;
				break;
			case SDLK_KP_1:
				punch_l = false;
				break;
			case SDLK_UP:
				up = false;
				break;
			case SDLK_LEFT:
				inputs2.Push(IN_LEFT_UP);
				left = false;
				break;
			case SDLK_RIGHT:
				inputs2.Push(IN_RIGHT_UP);
				right = false;
				break;
			}
		}
		if (event2.type == SDL_KEYDOWN && event2.key.repeat == 0)
		{
			switch (event2.key.keysym.sym)
			{
			case SDLK_q:
				punch_l = true;
				break;
			case SDLK_h:
				inputs2.Push(IN_H);
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
		inputs2.Push(IN_LEFT_AND_RIGHT);
	{
		if (left)
			inputs2.Push(IN_LEFT_DOWN);
		if (right)
			inputs2.Push(IN_RIGHT_DOWN);
	}

	if (up && down)
		inputs2.Push(IN_JUMP_AND_CROUCH);
	else
	{
		if (down)
			inputs2.Push(IN_CROUCH_DOWN);
		if (up)
			inputs2.Push(IN_JUMP);
	}
	if (punch_l)
	{
		inputs2.Push(IN_X);
	}
	return true;
}

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

p1_states ModuleInput::process_fsm(p2Qeue<p1_inputs>& inputs2)
{
	static p1_states state = ST_IDLE;
	p1_inputs last_input;

	while (inputs2.Pop(last_input))
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
						case IN_X:
						{
									 if (isOnLeft){
										 c_punch1 = App->colision->AddCollider({ position.x + 10, position.y - 75, 50, 10 }, COLLIDER_PUNCH_1, this);
									 }
									 else{
										 c_punch1 = App->colision->AddCollider({ position.x - 60, position.y - 75, 50, 10 }, COLLIDER_PUNCH_1, this);
									 }
									 punch_timer = SDL_GetTicks();
									 state = ST_PUNCH_STANDING_L;
						}
							break;
						case IN_H: state = ST_HIT; hit_timer = SDL_GetTicks();  break;
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

		case ST_PUNCH_STANDING_L:
		{
									switch (last_input)
									{
									case IN_PUNCH_FINISH: c_punch1->to_delete = true;  state = ST_IDLE;  break;
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