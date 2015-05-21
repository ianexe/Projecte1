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

	//Set timers
	jump_timer = 0;
	punch_timer_l = 0;
	punch_timer_h = 0;
	kick_timer_l = 0;
	hit_timer = 0;
	
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
	p1_states current_state = ST_UNKNOWN;
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


void ModulePlayer2::internal_input(p2Qeue<p1_inputs>& inputs)
{
	if (jump_timer > 0)
	{
		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			inputs.Push(IN_JUMP_N_FINISH);
			jump_timer = 0;
		}
	}

	if (punch_timer_l > 0)
	{
		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
			
		{
			inputs.Push(IN_PUNCH_L_FINISH);
			punch_timer_l = 0;
		}
	}

	if (punch_timer_h > 0)
	{
		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)

		{
			inputs.Push(IN_PUNCH_H_FINISH);
			punch_timer_h = 0;
		}
	}

	if (kick_timer_l > 0)
	{
		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)

		{
			inputs.Push(IN_KICK_L_FINISH);
			punch_timer_l = 0;
		}
	}

	if (hit_timer > 0)
	{
		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			inputs.Push(IN_HIT_FINISH);
			hit_timer = 0;
		}
	}
}

p1_states ModulePlayer2::process_fsm(p2Qeue<p1_inputs>& inputs)
{
	static p1_states state = ST_IDLE;
	p1_inputs last_input;

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
				case IN_JUMP_DOWN: state = ST_JUMPING_NEUTRAL; jump_timer = SDL_GetTicks();  break;
				case IN_CROUCH_DOWN: state = ST_CROUCHING; break;
				case IN_L_PUNCH:
					{
						if (isOnLeft){
							c_punch1 = App->colision->AddCollider({ position.x + 10, position.y - 75, 50, 10 }, COLLIDER_PUNCH_2, this);
						}
						else{
							c_punch1 = App->colision->AddCollider({ position.x - 60, position.y - 75, 50, 10 }, COLLIDER_PUNCH_2, this);
						}
						punch_timer_l = SDL_GetTicks();
						state = ST_PUNCH_STANDING_L;
					}
					break;

				case IN_H_PUNCH:
				{
					if (isOnLeft){
						c_punch2 = App->colision->AddCollider({ position.x + 10, position.y - 77, 50, 10 }, COLLIDER_PUNCH_2, this);
					}
					else
					{
						c_punch2 = App->colision->AddCollider({ position.x - 60, position.y - 77, 50, 10 }, COLLIDER_PUNCH_2, this);
					}
					punch_timer_h = SDL_GetTicks();
					state = ST_PUNCH_STANDING_H;
				}
				break;

				case IN_L_KICK:
				{
					if (isOnLeft){
						c_kick = App->colision->AddCollider({ position.x + 7, position.y - 92, 50, 50 }, COLLIDER_KICK_2, this);
					}
					else{
						c_kick = App->colision->AddCollider({ position.x - 57, position.y - 92, 50, 50 }, COLLIDER_KICK_2, this);
					}
					kick_timer_l = SDL_GetTicks();
					state = ST_KICK_STANDING_L;
				}
				break;

				case IN_HIT: state = ST_HIT; hit_timer = SDL_GetTicks();  break;
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
				//case IN_JUMP_DOWN: state = ST_JUMP_FORWARD; jump_timer = SDL_GetTicks();  break;
				case IN_CROUCH_DOWN: state = ST_CROUCHING; break;
				}
			}
			break;

			case ST_WALK_BACKWARD:
			{
				switch (last_input)
				{
				case IN_LEFT_UP: state = ST_IDLE; break;
				case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
			//	case IN_JUMP_DOWN: state = ST_JUMP_BACKWARD; jump_timer = SDL_GetTicks();  break;
				case IN_CROUCH_DOWN: state = ST_CROUCHING; break;
				}
			}
			break;

			case ST_JUMPING_NEUTRAL:
			{
				switch (last_input)
				{
				case IN_JUMP_N_FINISH: state = ST_IDLE; break;
			  //case IN_L_PUNCH: state = ST_PUNCH_NEUTRAL_JUMP; punch_timer = SDL_GetTicks(); break;
				}
			}
			break;

			case ST_PUNCH_NEUTRAL_JUMP:
			{
				switch (last_input)
				{
				case IN_JUMP_N_FINISH: state = ST_IDLE; break;
			//	case IN_PUNCH_FINISH: state = ST_JUMP_NEUTRAL; break;
				}
			}
			break;

			case ST_PUNCH_STANDING_L:
			{
				switch (last_input)
				{
				case IN_PUNCH_L_FINISH: c_punch1->to_delete = true;  state = ST_IDLE;  break;
				}
			}
			break;

			case ST_PUNCH_STANDING_H:
			{
				switch (last_input)
				{
				case IN_PUNCH_H_FINISH: c_punch2->to_delete = true;  state = ST_IDLE;  break;
				}
			}
			break;

			case ST_KICK_STANDING_L:
			{
				switch (last_input)
				{
				case IN_KICK_L_FINISH: c_kick->to_delete = true;  state = ST_IDLE;  break;
				}
			}
			break;
			case ST_CROUCHING:
			{
				switch (last_input)
				{
				//case IN_L_PUNCH: state = ST_PUNCH_CROUCH; punch_timer = SDL_GetTicks(); break;
				  case IN_CROUCH_UP: state = ST_IDLE; break;
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
	
	current_animation = &idle;
	current_state = ST_UNKNOWN;
		
	

	p1_states state2 = App->player2->process_fsm(inputs2);

		if (state2 != current_state)
		{
			switch (state2)
			{
			case ST_IDLE:
				//current_animation = &idle;
				break;
			case ST_HIT:
			
				break;

			case ST_WALK_FORWARD:{
				if (position.x < 860.0 && position.x < (App->renderer->OpCamera.x) + SCREEN_WIDTH)
				{
					current_animation = &forward;
					position.x += speed;
					collider->SetPos(position.x - 30, position.y - 90);
				}
			}
								 break;

			case ST_WALK_BACKWARD:
			{
				if (position.x > 0.0 && App->player2->position.x > (App->renderer->OpCamera.x) + 20)
				{
					current_animation = &backward;
					position.x -= speed;
					collider->SetPos(position.x - 30, position.y - 90);
				}
			}
			break;
			case ST_JUMPING_NEUTRAL:
				break;
		
			case ST_CROUCHING:
				break;
			
			case ST_PUNCH_STANDING_L:
				current_animation = &punch;
				collider->SetPos(position.x + 10, position.y - 75);
			break;
			case ST_PUNCH_STANDING_H:
				current_animation = &punch2;
				break;
			case ST_KICK_STANDING_L:
				current_animation = &kick;
				break;
	
		}
	
		current_state = state2;
		
	}
	
	// debug camera movement --------------------------------
	

	/*
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
	*/
	//Does attack if called
		/*
	if (doPunch)
	{
		/*current_animation = &punch;

		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			doPunch = false;
			isAttacking = false;
			c_punch1->to_delete = true;

		}*
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
	*/
	//Sets Collider position
	collider->SetPos(position.x - 30, position.y - 90);

	//Checks where player is facing

	if (App->player->position.x > App->player2->position.x)
		isOnLeft = true;
	else
		isOnLeft = false;

	App->player2->internal_input(inputs2);
	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	App->renderer->Blit(graphics, position.x - (r.w / 2), position.y - r.h, &r, 1, isOnLeft);

	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2)
{
	App->player->Health--;
}