#include "Application.h"
#include "ModulePlayer2.h"
#include "Globals.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	position.x = 380;
	position.y = 216;

	// shadow
	shadow.x = 743;
	shadow.y = 92;
	shadow.w = 68;
	shadow.h = 11;

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

	// jump animation (arcade sprite sheet)
	//jump.frames.PushBack({ 16, 847, 56, 85 });
	//jump.frames.PushBack({ 100, 823, 58, 109 });
	//jump.frames.PushBack({ 176, 805, 50, 127 });
	jump.frames.PushBack({ 239, 798, 66, 134 });
	jump.speed = 0.23f;

	// jump down animation (arcade sprite sheet)
	//jumpfalling.frames.PushBack({ 327, 813, 54, 119 });
	//jumpfalling.frames.PushBack({ 397, 810, 52, 122 });
	jumpfalling.frames.PushBack({ 464, 819, 60, 113 });

	jumpfalling.speed = 0.23f;

	// block
	block.frames.PushBack({ 442, 2335, 64, 92 });
	block.frames.PushBack({ 525, 2334, 64, 93 });
	block.frames.PushBack({ 525, 2334, 64, 93 });
	block.frames.PushBack({ 525, 2334, 64, 93 });
	block.speed = 0.1f;

	//crouch
	crouch.frames.PushBack({ 114, 1227, 58, 69 });
	crouch.frames.PushBack({ 196, 1235, 62, 61 });
	crouch.speed = 0.1f;

	//crouchidle
	crouchidle.frames.PushBack({ 196, 1235, 62, 61 });
	crouchidle.speed = 0.1f;

	// punch
	punch.frames.PushBack({ 19, 272, 64, 91 });
	punch.frames.PushBack({ 84, 272, 116, 91 });
	punch.frames.PushBack({ 19, 272, 64, 91 });
	punch.speed = 0.2f;

	// punch2
	punch2.frames.PushBack({ 333, 268, 90, 95 });
	punch2.frames.PushBack({ 422, 268, 118, 94 });
	punch2.frames.PushBack({ 422, 268, 118, 94 });
	punch2.frames.PushBack({ 333, 268, 90, 95 });
	punch2.speed = 0.2f;

	// kick
	kick.frames.PushBack({ 689, 267, 66, 92 });
	kick.frames.PushBack({ 777, 265, 114, 94 });
	kick.frames.PushBack({ 777, 265, 114, 94 });
	kick.frames.PushBack({ 689, 267, 66, 92 });
	kick.speed = 0.2f;

	// kick2
	kick2.frames.PushBack({ 16, 398, 79, 90 });
	kick2.frames.PushBack({ 99, 394, 98, 94 });
	kick2.frames.PushBack({ 198, 394, 133, 94 });
	kick2.frames.PushBack({ 351, 411, 108, 77 });
	kick2.frames.PushBack({ 482, 407, 98, 81 });
	kick2.speed = 0.2f;
	
	//Bools 
	isJumping = false;
	isOnLeft = false;
	isJumping = false;
	isFalling = false;
	isPunching_L = false;
	isPunching_H = false;
	isKicking_L = false;
	isKicking_H = false;
	doDefense = false;
	isAttacking = false;
	
	speed = 3;
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player");
	Health = 144;
	// Load SFC
	normalFX = App->audio->LoadFx("normal.wav");
	strongFX = App->audio->LoadFx("strong.wav");
	fallingFX = App->audio->LoadFx("falling.wav");
	graphics = App->textures->Load("ryu4.png"); // arcade version
	collider = App->colision->AddCollider({ position.x, position.y, 60, 90 }, COLLIDER_NEUTRAL_2);
	c_defense2 = App->colision->AddCollider({ position.x + 5, position.y + 10, 60, 40 }, COLLIDER_NONE);

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
	if (isJumping)
	{
		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			if (position.y < 135 && !isFalling)
			{
				isFalling = true;
			}

			if (position.y >= 216 && isFalling)
			{
				position.y = 216;
				App->audio->PlayFx(fallingFX);
				inputs.Push(IN_JUMP_N_FINISH);
			}

		}
	}

	/*if (isCrouching)
	{
	inputs.Push(IN_CROUCH_FINISH);
	//current_animation = &crouchidle;
	isCrouching = false;
	}
	}*/

	if (isPunching_L)
	{
		isAttacking = true;
		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
			
		{
			inputs.Push(IN_PUNCH_L_FINISH);
			isAttacking = isPunching_L = false;
		}
	}

	if (isPunching_H)
	{
		isAttacking = true;
		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)

		{
			inputs.Push(IN_PUNCH_H_FINISH);
			isAttacking = isPunching_H = false;
		}
	}

	if (isKicking_L)
	{
		isAttacking = true;
		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)

		{
			inputs.Push(IN_KICK_L_FINISH);
			isAttacking = isKicking_L = false;
		}
	}

	if (isKicking_H)
	{
		isAttacking = true;
		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			inputs.Push(IN_KICK_H_FINISH);
			isAttacking = isKicking_H = false;
		}
	}
	if (isHit)
	{
		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			inputs.Push(IN_HIT_FINISH);
			isHit = false;
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
				case IN_RIGHT_DOWN: state = ST_WALK_RIGHT; break;
				case IN_LEFT_DOWN: state = ST_WALK_LEFT; break;
				case IN_JUMP_DOWN: state = ST_JUMPING_NEUTRAL; isJumping = true;  break;
				case IN_CROUCH_DOWN: state = ST_CROUCHED; isCrouching = true; break;
				case IN_L_PUNCH:
					{
						if (isOnLeft){
							c_punch1 = App->colision->AddCollider({ position.x + 10, position.y - 75, 40, 10 }, COLLIDER_PUNCH_2, this);
						}
						else{
							c_punch1 = App->colision->AddCollider({ position.x - 50, position.y - 75, 40, 10 }, COLLIDER_PUNCH_2, this);
						}
						isPunching_L = true;
						App->audio->PlayFx(normalFX);
						state = ST_PUNCH_STANDING_L;
					}
					break;

				case IN_H_PUNCH:
				{
					if (isOnLeft){
						c_punch2 = App->colision->AddCollider({ position.x + 10, position.y - 77, 40, 10 }, COLLIDER_PUNCH_2, this);
					}
					else
					{
						c_punch2 = App->colision->AddCollider({ position.x - 50, position.y - 77, 40, 10 }, COLLIDER_PUNCH_2, this);
					}
					isPunching_H = true;
					App->audio->PlayFx(strongFX);
					state = ST_PUNCH_STANDING_H;
				}
				break;

				case IN_L_KICK:
				{
					if (isOnLeft){
						c_kick = App->colision->AddCollider({ position.x + 7, position.y - 85, 37, 25 }, COLLIDER_KICK_2, this);
					}
					else{
						c_kick = App->colision->AddCollider({ position.x - 57, position.y - 85, 37, 25 }, COLLIDER_KICK_2, this);
					}
					isKicking_L = true;
					App->audio->PlayFx(normalFX);
					state = ST_KICK_STANDING_L;
					
				}
				break;
				case IN_H_KICK:
				{
					if (isOnLeft)
					{
						c_kick2 = App->colision->AddCollider({ position.x + 15, position.y - 94, 45, 50 }, COLLIDER_KICK_2, this);
					}
					else
					{
						c_kick2 = App->colision->AddCollider({ position.x - 60, position.y - 94, 45, 50 }, COLLIDER_KICK_2, this);
					}
					isKicking_H = true;
					App->audio->PlayFx(strongFX);
					state = ST_KICK_STANDING_H;
				}
				break;
				//case IN_HIT: state = ST_HIT; isHit = true;  break;
				}
			}
			break;
			/*
			case ST_HIT:
			{
				switch (last_input)
				{
				case IN_HIT_FINISH: state = ST_IDLE; break;
				}
			}
			break;
			*/

			case ST_WALK_RIGHT:
			{
				switch (last_input)
				{
				case IN_RIGHT_UP: state = ST_IDLE; collider->rect.h = 90; doDefense = false; break;
				case IN_LEFT_AND_RIGHT: state = ST_IDLE; doDefense = false; break;
				//case IN_JUMP_DOWN: state = ST_JUMP_FORWARD; jump_timer = SDL_GetTicks();  break;
				//case IN_CROUCH_DOWN: state = ST_CROUCHING; break;
				}
			}
			break;

			case ST_WALK_LEFT:
			{
				switch (last_input)
				{
				case IN_LEFT_UP: state = ST_IDLE; doDefense = false; break;
				case IN_LEFT_AND_RIGHT: state = ST_IDLE; doDefense = false; break;
				//case IN_JUMP_DOWN: state = ST_JUMP_BACKWARD; jump_timer = SDL_GetTicks();  break;
				//case IN_CROUCH_DOWN: state = ST_CROUCHING; break;
				}
			}
			break;

			case ST_JUMPING_NEUTRAL:
			{
				switch (last_input)
				{
				//case IN_JUMP_UP: isFalling = true; break;
				case IN_JUMP_N_FINISH: state = ST_IDLE; isFalling = isJumping = false; break;
			  //case IN_L_PUNCH: state = ST_PUNCH_NEUTRAL_JUMP; punch_timer = SDL_GetTicks(); break;
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

			case ST_KICK_STANDING_H:
			{
				switch (last_input)
				{
				case IN_KICK_H_FINISH: c_kick2->to_delete = true; state = ST_IDLE;  break;
				}
			}
			break;

			/*case ST_CROUCHING:
			{
			switch (last_input)
			{
			case IN_CROUCH_FINISH: state = ST_CROUCHED; break;
			case IN_CROUCH_UP: state = ST_IDLE; break;
			}
			}
			break;*/

			case ST_CROUCHED:
			{
				switch (last_input)
				{
				case IN_CROUCH_UP: state = ST_IDLE; collider->rect.h = 90; isCrouching = false; break;
					//case IN_L_PUNCH: state = ST_PUNCH_CROUCH; punch_timer = SDL_GetTicks(); break;

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
	
	current_animation = &idle;
	current_state = ST_UNKNOWN;
		
	

	p1_states state2 = App->player2->process_fsm(inputs2);

		if (state2 != current_state)
		{
			switch (state2)
			{
			case ST_IDLE:
				//current_animation = &idle;
				if (!doDefense)
				{
					c_defense2->type = COLLIDER_NONE;
				}
				collider->rect.h = 90;
				break;
			/*case ST_HIT:
			
				break;*/

			case ST_WALK_RIGHT:
			{
				if (!isOnLeft && App->player->isAttacking)
				{
					doDefense = true;
				}

				else
				{
					doDefense = false;
				}

				if (position.x < 860.0 && position.x < (App->renderer->OpCamera.x) + SCREEN_WIDTH && !doDefense)
				{
					if (position.x < App->player->position.x)
						current_animation = &forward;
					else
						current_animation = &backward;
					position.x += speed;
					collider->SetPos(position.x - 30, position.y - 90);
				}

				

				if (doDefense)
				{
					current_animation = &block;

					c_defense2->type = COLLIDER_DEFENSE_2;
				}
			}
				
			 break;

			case ST_WALK_LEFT:
			{
				if (isOnLeft && App->player->isAttacking)
				{
					doDefense = true;
				}

				else
				{
					doDefense = false;
				}

				if (position.x > 0.0 && position.x > (App->renderer->OpCamera.x) + 20 && !doDefense)
				{
					if (position.x > App->player->position.x)
						current_animation = &forward;
					else
						current_animation = &backward;
					position.x -= speed;
					collider->SetPos(position.x - 30, position.y - 90);
				}

				if (doDefense)
				{
					current_animation = &block;

					c_defense2->type = COLLIDER_DEFENSE_2;
				}
			}
			break;
			case ST_JUMPING_NEUTRAL:
				if (!isFalling)
				{
					current_animation = &jump;
					position.y -= 5;
					/*
					
					collider->rect.h = 90;
					collider->SetPos(position.x - 30, position.y + 90);

					*/

				}
				else
				{
					position.y += 5;
					current_animation = &jumpfalling;
				}
				collider->rect.h = 90;
				break;
		

				/*case ST_CROUCHING:
				current_animation = &crouch;
				break;*/
			
			case ST_CROUCHED:
				current_animation = &crouchidle;
				collider->rect.h = 60;
				break;

			case ST_PUNCH_STANDING_L:
				current_animation = &punch;
				break;

			case ST_PUNCH_STANDING_H:
				current_animation = &punch2;
				break;
			case ST_KICK_STANDING_L:
				current_animation = &kick;
				break;
			case ST_KICK_STANDING_H:
				current_animation = &kick2;
				break;
	
		}
	}
	

	//Checks where player is facing

	if (App->player->position.x > App->player2->position.x)
		isOnLeft = true;
	else
		isOnLeft = false;

	c_defense2->SetPos(position.x - 30, position.y - 90);
	collider->SetPos(position.x - 30, position.y - 90);

	if (isJumping)
	{
		c_defense2->SetPos(position.x - 30, position.y - 150);
		collider->SetPos(position.x - 30, position.y - 150);
	}

	if (isFalling)
	{
		c_defense2->SetPos(position.x - 30, position.y - 90);
		collider->SetPos(position.x - 30, position.y - 90);

	}

	if (isCrouching)
	{
		collider->SetPos(position.x - 30, position.y - 60);
		c_defense2->SetPos(position.x - 30, position.y - 60);
	}

	current_state = state2;
	App->player2->internal_input(inputs2);
	
	// Draw everything --------------------------------------

	SDL_Rect r = current_animation->GetCurrentFrame();
	App->renderer->Blit(graphics, position.x - 35, 208, &shadow, 1.0f);
	App->renderer->Blit(graphics, position.x - (r.w / 2), position.y - r.h, &r, 1, isOnLeft);

	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2)
{
	if (App->player->doDefense == false)
		App->player->Health--;
}