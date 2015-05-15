#include "Application.h"
#include "ModulePlayer2.h"
#include "Globals.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	position.x = 380;
	position.y = 216;
	// idle animation (arcade sprite sheet)
	idle.frames.PushBack({ 7, 14, 60, 90 });
	idle.frames.PushBack({ 95, 15, 60, 89 });
	idle.frames.PushBack({ 184, 14, 60, 90 });
	idle.frames.PushBack({ 276, 11, 60, 93 });
	idle.frames.PushBack({ 366, 12, 60, 92 });
	idle.speed = 0.2f;

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	forward.frames.PushBack({ 78, 131, 60, 88 });
	forward.frames.PushBack({ 162, 128, 64, 92 });
	forward.frames.PushBack({ 259, 128, 63, 90 });
	forward.frames.PushBack({ 352, 128, 54, 91 });
	forward.frames.PushBack({ 432, 131, 50, 89 });
	forward.speed = 0.1f;

	// walk backward animation (arcade sprite sheet)
	backward.frames.PushBack({ 542, 131, 61, 87 });
	backward.frames.PushBack({ 628, 129, 59, 90 });
	backward.frames.PushBack({ 713, 128, 57, 90 });
	backward.frames.PushBack({ 797, 127, 57, 90 });
	backward.frames.PushBack({ 883, 128, 58, 91 });
	backward.frames.PushBack({ 974, 129, 57, 89 });
	backward.speed = 0.1f;

	// punch
	punch.frames.PushBack({ 19, 272, 64, 91 });
	punch.frames.PushBack({ 84, 272, 116, 91 });
	punch.frames.PushBack({ 19, 272, 64, 91 });
	punch.speed = 0.1f;

	// punch2
	punch2.frames.PushBack({ 333, 268, 90, 95 });
	punch2.frames.PushBack({ 422, 268, 118, 94 });
	punch2.frames.PushBack({ 333, 268, 90, 95 });
	punch2.speed = 0.1f;

	// kick
	kick.frames.PushBack({ 689, 267, 66, 92 });
	kick.frames.PushBack({ 777, 265, 114, 94 });
	kick.frames.PushBack({ 689, 267, 66, 92 });
	kick.speed = 0.1f;

	
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player");
	Health = 100;
	
	graphics = App->textures->Load("ryu4.png"); // arcade version
	collider = App->colision->AddCollider({ position.x, position.y, 60, 90 }, COLLIDER_NEUTRAL_2);
	p2_states current_state = _2_ST_UNKNOWN;

	jump_timer = 0;
	punch_timer = 0;
	hit_timer = 0;
	return true;
}

// Unload assets
bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	position.x = 380;
	position.y = 216;
	return true;
}

Uint32 jump_timer = 0;
Uint32 punch_timer = 0;
Uint32 hit_timer = 0;

bool ModulePlayer2::external_input(p2Qeue<p2_inputs>& inputs)
{
	static bool left = false;
	static bool right = false;
	static bool down = false;
	static bool up = false;
	static bool punch_l = false;

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
			case SDLK_KP_1:
				punch_l = false;
				break;
			case SDLK_DOWN:
				inputs.Push(_2_IN_CROUCH_UP);
				down = false;
				break;
			case SDLK_UP:
				up = false;
				break;
			case SDLK_LEFT:
				inputs.Push(_2_IN_LEFT_UP);
				left = false;
				break;
			case SDLK_RIGHT:
				inputs.Push(_2_IN_RIGHT_UP);
				right = false;
				break;
			}
		}
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_KP_1:
				punch_l = false;
				break;
			case SDLK_j:
				inputs.Push(_2_IN_H);
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
		inputs.Push(_2_IN_LEFT_AND_RIGHT);
	{
		if (left)
			inputs.Push(_2_IN_LEFT_DOWN);
		if (right)
			inputs.Push(_2_IN_RIGHT_DOWN);
	}

	if (up && down)
		inputs.Push(_2_IN_JUMP_AND_CROUCH);
	else
	{
		if (down)
			inputs.Push(_2_IN_CROUCH_DOWN);
		if (up)
			inputs.Push(_2_IN_JUMP);
	}

	if (punch_l)
	{
		inputs.Push(_2_IN_X);
	}
	return true;
}

void ModulePlayer2::internal_input(p2Qeue<p2_inputs>& inputs)
{
	if (jump_timer > 0)
	{
		if (SDL_GetTicks() - jump_timer > JUMP_TIME)
		{
			inputs.Push(_2_IN_JUMP_FINISH);
			jump_timer = 0;
		}
	}

	if (punch_timer > 0)
	{
		if (SDL_GetTicks() - punch_timer > PUNCH_TIME)
		{
			inputs.Push(_2_IN_PUNCH_FINISH);
			punch_timer = 0;
		}
	}

	if (hit_timer > 0)
	{
		if (SDL_GetTicks() - hit_timer > HIT_TIME)
		{
			inputs.Push(_2_IN_HIT_FINISH);
			punch_timer = 0;
		}
	}
}

p2_states ModulePlayer2::process_fsm(p2Qeue<p2_inputs>& inputs)
{
	static p2_states state = _2_ST_IDLE;
	p2_inputs last_input;
	int speed = 3;

	while (inputs.Pop(last_input))
	{
		switch (state)
		{
		case _2_ST_IDLE:
		{
			switch (last_input)
			{
			case _2_IN_RIGHT_DOWN: state = _2_ST_WALK_FORWARD; break;
			case _2_IN_LEFT_DOWN: state = _2_ST_WALK_BACKWARD; break;
			case _2_IN_JUMP: state = _2_ST_JUMP_NEUTRAL; jump_timer = SDL_GetTicks();  break;
			case _2_IN_CROUCH_DOWN: state = _2_ST_CROUCH; break;
			case _2_IN_X: state = _2_ST_PUNCH_STANDING_L; punch_timer = SDL_GetTicks();  break;
			case _2_IN_H: state = _2_ST_HIT; hit_timer = SDL_GetTicks();  break;
			}
		}
		break;

		case _2_ST_HIT:
		{
			switch (last_input)
			{
			case _2_IN_HIT_FINISH: state = _2_ST_IDLE; break;
			}
		}
		break;


		case _2_ST_WALK_FORWARD:
		{
			switch (last_input)
			{
			case _2_IN_RIGHT_UP: state = _2_ST_IDLE; break;
			case _2_IN_LEFT_AND_RIGHT: state = _2_ST_IDLE; break;
			case _2_IN_JUMP: state = _2_ST_JUMP_FORWARD; jump_timer = SDL_GetTicks();  break;
			case _2_IN_CROUCH_DOWN: state = _2_ST_CROUCH; break;
			}
		}
		break;

		case _2_ST_WALK_BACKWARD:
		{
			switch (last_input)
			{
			case _2_IN_LEFT_UP: state = _2_ST_IDLE; break;
			case _2_IN_LEFT_AND_RIGHT: state = _2_ST_IDLE; break;
			case _2_IN_JUMP: state = _2_ST_JUMP_BACKWARD; jump_timer = SDL_GetTicks();  break;
			case _2_IN_CROUCH_DOWN: state = _2_ST_CROUCH; break;
			}
		}
		break;

		case _2_ST_JUMP_NEUTRAL:
		{
			switch (last_input)
			{
			case _2_IN_JUMP_FINISH: state = _2_ST_IDLE; break;
			case _2_IN_X: state = _2_ST_PUNCH_NEUTRAL_JUMP; punch_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case _2_ST_JUMP_FORWARD:
		{
			switch (last_input)
			{
			case _2_IN_JUMP_FINISH: state = _2_ST_IDLE; break;
			case _2_IN_X: state = _2_ST_PUNCH_FORWARD_JUMP; punch_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case _2_ST_JUMP_BACKWARD:
		{
			switch (last_input)
			{
			case _2_IN_JUMP_FINISH: state = _2_ST_IDLE; break;
			case _2_IN_X: state = _2_ST_PUNCH_BACKWARD_JUMP; punch_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case _2_ST_PUNCH_NEUTRAL_JUMP:
		{
			switch (last_input)
			{
			case _2_IN_JUMP_FINISH: state = _2_ST_IDLE; break;
			case _2_IN_PUNCH_FINISH: state = _2_ST_JUMP_NEUTRAL; break;
			}
		}
		break;

		case _2_ST_PUNCH_FORWARD_JUMP:
		{
			switch (last_input)
			{
			case _2_IN_JUMP_FINISH: state = _2_ST_IDLE; break;
			case _2_IN_PUNCH_FINISH: state = _2_ST_JUMP_FORWARD; break;
			}
		}
		break;

		case _2_ST_PUNCH_BACKWARD_JUMP:
		{
			switch (last_input)
			{
			case _2_IN_JUMP_FINISH: state = _2_ST_IDLE; break;
			case _2_IN_PUNCH_FINISH: state = _2_ST_JUMP_BACKWARD; break;
			}
		}
		break;

		case _2_ST_PUNCH_STANDING_L:
		{
			switch (last_input)
			{
			case _2_IN_PUNCH_FINISH: state = _2_ST_IDLE; break;
			}
		}
		break;

		case _2_ST_CROUCH:
		{
			switch (last_input)
			{
			case _2_IN_X: state = _2_ST_PUNCH_CROUCH; punch_timer = SDL_GetTicks(); break;
			case _2_IN_CROUCH_UP: state = _2_ST_IDLE; break;

			}
		}
		break;
		case _2_ST_PUNCH_CROUCH:
		{
			switch (last_input)
			{

			case _2_IN_PUNCH_FINISH: state = _2_ST_IDLE; break;
			}
		}
		break;
		}
	}

	return state;
}

	


// Update: draw background
update_status ModulePlayer2::Update()
{
	if (Health < 0)
		Health = 0;
	int speed = 3;
	
	//Els sprites estan ben ficats
	Animation* current_animation = &idle;

	collider->SetPos(position.x - 30, position.y - 90);

	current_state = _2_ST_UNKNOWN;
	//printf("Listening for WASD + SPACE:\n");

	if (external_input(inputs))
	{
		internal_input(inputs);

		p2_states state = process_fsm(inputs);

		if (state != current_state)
		{
			switch (state)
			{
			case _2_ST_IDLE:
				current_animation = &idle;
				break;
			case _2_ST_HIT:
			
				break;
			case _2_ST_WALK_FORWARD:
				if (position.x < 896.0 && position.x < (App->renderer->OpCamera.x) + SCREEN_WIDTH)
				{
					current_animation = &forward;
					position.x += speed;

					collider->SetPos(position.x - 30, position.y - 90);

					//App->player2_col->AddCollider(detection, COLLIDER_NEUTRAL_2, NULL);

				}
				break;
			case _2_ST_WALK_BACKWARD:
				if (position.x > 0.0 && position.x > (App->renderer->OpCamera.x) + 10)
				{
					current_animation = &forward;
					position.x -= speed;
					collider->SetPos(position.x - 30, position.y - 90);
				}
				break;
			case _2_ST_JUMP_NEUTRAL:
			
				break;
			case _2_ST_JUMP_FORWARD:
	
				break;
			case _2_ST_JUMP_BACKWARD:
			
				break;
			case _2_ST_CROUCH:
				
				break;
			case _2_ST_PUNCH_CROUCH:
		
				break;
			case _2_ST_PUNCH_STANDING_L:
				current_animation = &punch;
				if (isOnLeft){

					c_punch1 = App->colision->AddCollider({ position.x + 10, position.y - 75, 60, 10 }, COLLIDER_PUNCH_2, this);
				}
				else{

					c_punch1 = App->colision->AddCollider({ position.x - 60, position.y - 75, 60, 10 }, COLLIDER_PUNCH_2, this);
				}
				break;
			case _2_ST_PUNCH_NEUTRAL_JUMP:

				break;
			case _2_ST_PUNCH_FORWARD_JUMP:
				break;
			case _2_ST_PUNCH_BACKWARD_JUMP:

				break;
			}
		}
		current_state = state;
	}

	// debug camera movement --------------------------------
	


	if ((App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) && (!isAttacking))
	{	
	}

	if ((App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) && (!isAttacking))
	{
	}

	if ((App->input->GetKey(SDL_SCANCODE_KP_1) == KEY_DOWN) && (!isAttacking))
	{
		doPunch = true;
		isAttacking = true;
		
	}

	if ((App->input->GetKey(SDL_SCANCODE_KP_2) == KEY_DOWN) && (!isAttacking))
	{
		doPunch2 = true;
		isAttacking = true;
		if (isOnLeft){
			c_punch2 = App->colision->AddCollider({ position.x + 10, position.y - 77, 50, 10 }, COLLIDER_PUNCH_2, this);
		}
		else
		{
			c_punch2 = App->colision->AddCollider({ position.x - 60, position.y - 77, 50, 10 }, COLLIDER_PUNCH_2, this);

		}
	}

	if ((App->input->GetKey(SDL_SCANCODE_KP_3) == KEY_DOWN) && (!isAttacking))
	{
		doKick = true;
		isAttacking = true;
		if (isOnLeft){
			c_kick = App->colision->AddCollider({ position.x + 7.0, position.y - 92, 50, 50 }, COLLIDER_KICK_2, this);
		}
		else{
			c_kick = App->colision->AddCollider({ position.x - 57.0, position.y - 92, 50, 50 }, COLLIDER_KICK_2, this);
		}
		
	}

	//Does attack if called

	if (doPunch)
	{
		/*current_animation = &punch;

		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			doPunch = false;
			isAttacking = false;
			c_punch1->to_delete = true;

		}*/
	}


	if (doPunch2)
	{
		current_animation = &punch2;
		
		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			doPunch2 = false;
			isAttacking = false;
			c_punch2->to_delete = true;
		}
	}

	if (doKick)
	{
		current_animation = &kick;
		
		

		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			doKick = false;
			isAttacking = false;
			c_kick->to_delete = true;
		}
	}

	//Checks where player is facing

	if (App->player->position.x > App->player2->position.x)
		isOnLeft = true;
	else
		isOnLeft = false;

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->renderer->Blit(graphics, position.x - (r.w / 2), position.y - r.h, &r, 1, isOnLeft);



	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2)
{
	App->player->Health--;
}