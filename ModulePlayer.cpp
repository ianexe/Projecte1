#include "Application.h"
#include "ModulePlayer.h"
#include "Globals.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	position.x = 80;
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
	jump.frames.PushBack({ 100, 823, 60, 104 });
	jump.frames.PushBack({ 176, 827, 54, 100 });
	jump.frames.PushBack({ 251, 828, 54, 99 });
	jump.frames.PushBack({ 327, 829, 62, 98 });
	jump.loop = false;
	jump.speed = 0.23f;

	// jump fall animation (arcade sprite sheet)
	jumpfalling.frames.PushBack({ 397, 826, 48, 101 });
	jumpfalling.frames.PushBack({ 464, 818, 60, 109 });
	jumpfalling.loop = false;
	jumpfalling.speed = 0.23f;

	// jump forward animation (arcade sprite sheet)
	jumpforward.frames.PushBack({ 581, 823, 68, 103 });
	jumpforward.frames.PushBack({ 668, 828, 62, 98 });
	jumpforward.frames.PushBack({ 744, 826, 120, 100 });
	jumpforward.frames.PushBack({ 857, 806, 60, 120 });
	jumpforward.loop = false;
	jumpforward.speed = 0.23f;

	// jump forward fall animation (arcade sprite sheet)

	jumpforwardfalling.frames.PushBack({ 917, 823, 132, 103 });
	jumpforwardfalling.frames.PushBack({ 1064, 821, 74, 105 });
	jumpforwardfalling.frames.PushBack({ 1149, 817, 68, 109 });
	jumpforwardfalling.loop = false;
	jumpforwardfalling.speed = 0.23f;

	// jump backward animation (arcade sprite sheet)
	jumpbackward.frames.PushBack({ 1149, 817, 68, 109 });
	jumpbackward.frames.PushBack({ 1064, 821, 74, 105 });
	jumpbackward.frames.PushBack({ 917, 823, 132, 103 });
	jumpbackward.frames.PushBack({ 857, 806, 60, 120 });
	jumpbackward.loop = false;
	jumpbackward.speed = 0.23f;

	// jump backward fall animation (arcade sprite sheet)
	jumpbackwardfalling.frames.PushBack({ 744, 826, 120, 100 });
	jumpbackwardfalling.frames.PushBack({ 668, 828, 62, 98 });
	jumpbackwardfalling.frames.PushBack({ 581, 823, 68, 103 });
	jumpbackwardfalling.loop = false;
	jumpbackwardfalling.speed = 0.23f;

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
	
	// hadouken move
	hadoukenmove.frames.PushBack({ 34, 1545, 100, 90 });
	hadoukenmove.frames.PushBack({ 135, 1551, 102, 84 });
	hadoukenmove.frames.PushBack({ 244, 1552, 104, 83 });
	hadoukenmove.frames.PushBack({ 350, 1558, 113, 77 });
	hadoukenmove.loop = false;
	hadoukenmove.speed = 0.2f;

	// crouch punch
	crouchpunch.frames.PushBack({ 24, 1344, 72, 61 });
	crouchpunch.frames.PushBack({ 93, 1344, 120, 61 });
	crouchpunch.frames.PushBack({ 24, 1344, 72, 61 });
	crouchpunch.speed = 0.2f;

	// crouch kick
	crouchkick.frames.PushBack({ 890, 1342, 86, 64 });
	crouchkick.frames.PushBack({ 960, 1342, 142, 64 });
	crouchkick.frames.PushBack({ 890, 1342, 86, 64 });
	crouchkick.speed = 0.2f;

	// jump punch
	jumppunch.frames.PushBack({ 26, 1099, 60, 76 });
	jumppunch.frames.PushBack({ 100, 1102, 62, 73 });
	jumppunch.frames.PushBack({ 182, 1108, 80, 67 });
	jumppunch.loop = false;
	jumppunch.speed = 0.23f;

	// jump kick
	jumpkick.frames.PushBack({ 310, 1099, 66, 76 });
	jumpkick.frames.PushBack({ 392, 1103, 78, 72 });
	jumpkick.frames.PushBack({ 456, 1104, 132, 71 });
	jumpkick.loop = false;
	jumpkick.speed = 0.23f;

	//Timer
	

	//Bools 
	isJumping = false;
	isOnLeft = false;
	isJumping= false;
	isJumpingB = false;
	isJumpingF = false;
	isFalling= false;
	isGoingRight = false;
	isGoingLeft = false;
	isPunching_L= false;
	isPunching_H= false;
	isKicking_L= false;
	isKicking_H= false;
	doDefense = false;
	isAttacking = false;

	speed = 3;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	Health = 144;
	// Load SFC
	normalFX = App->audio->LoadFx("normal.wav");
	strongFX = App->audio->LoadFx("strong.wav");
	fallingFX = App->audio->LoadFx("falling.wav");

	graphics = App->textures->Load("ryu4.png"); // arcade version

	collider = App->colision->AddCollider({ position.x, position.y, 60, 90 }, COLLIDER_NEUTRAL_1);
	c_defense = App->colision->AddCollider({ position.x + 5, position.y + 10, 60, 40 }, COLLIDER_NONE);

	p1_states current_state = ST_UNKNOWN;

	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	position.x = 80;
	position.y = 216;
	return true;
}

//State machine functions


void ModulePlayer::internal_input(p2Qeue<p1_inputs>& inputs)
{
	if (isJumping)
	{
		if (position.y < 115 && !isFalling)
		{
			isFalling = true;
		}
		
		if (position.y >= 216 && isFalling)
		{
			position.y = 216;
			App->audio->PlayFx(fallingFX);
			jump.setToZero();
			jumpforward.setToZero();
			jumpbackward.setToZero();
			isJumping = false;
			isJumpingF = false;
			isJumpingB = false;
			isGoingLeft = false;
			isGoingRight = false;
			
			inputs.Push(IN_JUMP_N_FINISH);
		}
			
	}

	/*if (isCrouching)
	{
		inputs.Push(IN_CROUCH_FINISH);
			//current_animation = &crouchidle;
		isCrouching = false;
		}
	}*/

	//Attacks
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

	if (isCrouchKicking)
	{
		isAttacking = true;
		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			inputs.Push(IN_KICK_CROUCH_FINISH);
			isAttacking = isCrouchKicking = false;
		}
	}

	if (isJumpKicking)
	{
		isAttacking = true;
		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			inputs.Push(IN_KICK_JUMP_FINISH);
			isAttacking = isJumpKicking = false;
		}
	}

	if (isCrouchPunching)
	{
		isAttacking = true;
		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			inputs.Push(IN_PUNCH_CROUCH_FINISH);
			isAttacking = isCrouchPunching = false;
		}
	}

	if (isJumpPunching)
	{
		isAttacking = true;
		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			inputs.Push(IN_PUNCH_JUMP_FINISH);
			isAttacking = isJumpPunching = false;
		}
	}

	if (isHit)
	{
		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			inputs.Push(IN_HIT_FINISH);
			isHit = 0;
		}
	}
}


p1_states ModulePlayer::process_fsm(p2Qeue<p1_inputs>& inputs)
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
			case IN_RIGHT_DOWN: state = ST_WALK_RIGHT;	break;
			case IN_LEFT_DOWN: state = ST_WALK_LEFT;break;
			case IN_JUMP_DOWN: state = ST_JUMPING_NEUTRAL; isJumping = true;  break;
			case IN_CROUCH_DOWN: state = ST_CROUCHED; isCrouching = true; break;
			/*
			case IN_LEFT_AND_UP:
			{
				isJumping = true;
				if (position.x < App->player2->position.x)
				{
					state = ST_JUMP_BACKWARD;
					isJumpingB = true;
				}

				else if (position.x > App->player2->position.x)
				{
					state = ST_JUMP_FORWARD;
					isJumpingF = true;
				}
			}
			break;
			*/

			case IN_L_PUNCH:
			{
				if (isOnLeft){
					c_punch1 = App->colision->AddCollider({ position.x + 10, position.y - 75, 40, 10 }, COLLIDER_PUNCH_1, this);
				}
				else{
					c_punch1 = App->colision->AddCollider({ position.x - 50, position.y - 75, 40, 10 }, COLLIDER_PUNCH_1, this);
				}
				isPunching_L = true;
				App->audio->PlayFx(normalFX);
				state = ST_PUNCH_STANDING_L;
			}
			break;

			case IN_H_PUNCH:
			{
				if (isOnLeft){
					c_punch2 = App->colision->AddCollider({ position.x + 10, position.y - 77, 40, 10 }, COLLIDER_PUNCH_1, this);
				}
				else
				{
					c_punch2 = App->colision->AddCollider({ position.x - 50, position.y - 77, 40, 10 }, COLLIDER_PUNCH_1, this);
				}
				isPunching_H = true;
				App->audio->PlayFx(strongFX);
				state = ST_PUNCH_STANDING_H;
			}
			break;

			case IN_L_KICK:
			{
				if (isOnLeft)
				{
					c_kick = App->colision->AddCollider({ position.x + 7, position.y - 92, 37, 50 }, COLLIDER_KICK_1, this);
				}
				else
				{
					c_kick = App->colision->AddCollider({ position.x - 57, position.y - 92,37 , 50 }, COLLIDER_KICK_1, this);
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
					c_kick2 = App->colision->AddCollider({ position.x + 15, position.y - 94, 45, 50 }, COLLIDER_KICK_1, this);
				}
				else
				{
					c_kick2 = App->colision->AddCollider({ position.x - 60, position.y - 94, 45, 50 }, COLLIDER_KICK_1, this);
				}
				isKicking_H = true;
				App->audio->PlayFx(strongFX);
				state = ST_KICK_STANDING_H;
			}
			break;

			case IN_HIT: state = ST_HIT; isHit = true;break;
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

		case ST_WALK_RIGHT:
		{
			switch (last_input)
			{
			case IN_RIGHT_UP: state = ST_IDLE; doDefense = false; break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; doDefense = false;  break;
			case IN_JUMP_DOWN:
			{
				isJumping = true;
				if (position.x < App->player2->position.x)
				{
					state = ST_JUMP_FORWARD;
					isGoingRight = true;
					isJumpingF = true;
				}
					
				else if (position.x > App->player2->position.x)
				{
					state = ST_JUMP_BACKWARD;
					isGoingRight = true;
					isJumpingB = true;
				}
				
			}
			break;
				//case IN_JUMP_DOWN: state = ST_JUMP_FORWARD; jump_timer = SDL_GetTicks();  break;
				/**
				*TODO: COLISIO CROUCH
				**/
			//case IN_CROUCH_DOWN: state = ST_CROUCHING; break;
			}
		}
		break;


		case ST_WALK_LEFT:
		{
			switch (last_input)
			{
			case IN_LEFT_UP: state = ST_IDLE; doDefense = false;  break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; doDefense = false; break;
			case IN_JUMP_DOWN:
			{
				isJumping = true;
				if (position.x < App->player2->position.x)
				{
					state = ST_JUMP_BACKWARD;
					isGoingLeft = true;
					isJumpingB = true;
					
				}

				else if (position.x > App->player2->position.x)
				{
					state = ST_JUMP_FORWARD;
					isGoingLeft = true;
					isJumpingF = true;
				}
			}
			break;
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
			case IN_L_PUNCH:
			{
				/*
				if (isOnLeft){
				c_punch1 = App->colision->AddCollider({ position.x + 10, position.y - 75, 40, 10 }, COLLIDER_PUNCH_1, this);
				}
				else{
				c_punch1 = App->colision->AddCollider({ position.x - 50, position.y - 75, 40, 10 }, COLLIDER_PUNCH_1, this);
				}
				*/
				isJumpPunching = true;
				App->audio->PlayFx(normalFX);
				state = ST_PUNCH_JUMP;
			}
			break;

			case IN_L_KICK:
			{
				/*
				if (isOnLeft){
				c_punch1 = App->colision->AddCollider({ position.x + 10, position.y - 75, 40, 10 }, COLLIDER_PUNCH_1, this);
				}
				else{
				c_punch1 = App->colision->AddCollider({ position.x - 50, position.y - 75, 40, 10 }, COLLIDER_PUNCH_1, this);
				}
				*/
				isJumpKicking = true;
				App->audio->PlayFx(normalFX);
				state = ST_KICK_JUMP;
			}
			break;

			case IN_JUMP_N_FINISH: 
				state = ST_IDLE; 
				isFalling = isJumping = false;
				jumpfalling.setToZero();
				break;
			//case IN_L_PUNCH: state = ST_PUNCH_NEUTRAL_JUMP; punch_timer = SDL_GetTicks(); break;

			}
		}
		break;

		case ST_JUMP_FORWARD:
		{
			switch (last_input)
			{
				
			case IN_L_PUNCH:
			{
				/*
				if (isOnLeft){
				c_punch1 = App->colision->AddCollider({ position.x + 10, position.y - 75, 40, 10 }, COLLIDER_PUNCH_1, this);
				}
				else{
				c_punch1 = App->colision->AddCollider({ position.x - 50, position.y - 75, 40, 10 }, COLLIDER_PUNCH_1, this);
				}
				*/
				isJumpPunching = true;
				App->audio->PlayFx(normalFX);
				state = ST_PUNCH_JUMP;
			}
			break;

			case IN_L_KICK:
			{
				/*
				if (isOnLeft){
				c_punch1 = App->colision->AddCollider({ position.x + 10, position.y - 75, 40, 10 }, COLLIDER_PUNCH_1, this);
				}
				else{
				c_punch1 = App->colision->AddCollider({ position.x - 50, position.y - 75, 40, 10 }, COLLIDER_PUNCH_1, this);
				}
				*/
				isJumpKicking = true;
				App->audio->PlayFx(normalFX);
				state = ST_KICK_JUMP;
			}
			break;

			case IN_JUMP_N_FINISH:
				state = ST_IDLE;
				isFalling = isJumping = isJumpingF = false;
				jumpforwardfalling.setToZero();
				break;
				//case IN_L_PUNCH: state = ST_PUNCH_NEUTRAL_JUMP; punch_timer = SDL_GetTicks(); break;

			}
		}
		break;

		case ST_JUMP_BACKWARD:
		{
			switch (last_input)
			{

			case IN_L_PUNCH:
			{
				/*
				if (isOnLeft){
				c_punch1 = App->colision->AddCollider({ position.x + 10, position.y - 75, 40, 10 }, COLLIDER_PUNCH_1, this);
				}
				else{
				c_punch1 = App->colision->AddCollider({ position.x - 50, position.y - 75, 40, 10 }, COLLIDER_PUNCH_1, this);
				}
				*/
				isJumpPunching = true;
				App->audio->PlayFx(normalFX);
				state = ST_PUNCH_JUMP;
			}
			break;

			case IN_L_KICK:
			{
				/*
				if (isOnLeft){
				c_punch1 = App->colision->AddCollider({ position.x + 10, position.y - 75, 40, 10 }, COLLIDER_PUNCH_1, this);
				}
				else{
				c_punch1 = App->colision->AddCollider({ position.x - 50, position.y - 75, 40, 10 }, COLLIDER_PUNCH_1, this);
				}
				*/
				isJumpKicking = true;
				App->audio->PlayFx(normalFX);
				state = ST_KICK_JUMP;
			}
			break;

			case IN_JUMP_N_FINISH:
				state = ST_IDLE;
				isFalling = isJumping = isJumpingB = false;
				jumpbackwardfalling.setToZero();
				break;
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
			case IN_L_PUNCH:
			{
				
				if (isOnLeft){
					c_punch1 = App->colision->AddCollider({ position.x + 10, position.y - 48, 40, 10 }, COLLIDER_PUNCH_1, this);
				}
				else{
					c_punch1 = App->colision->AddCollider({ position.x - 50, position.y - 48, 40, 10 }, COLLIDER_PUNCH_1, this);
				}
				
				isCrouchPunching = true;
				App->audio->PlayFx(normalFX);
				state = ST_PUNCH_CROUCH;
			}
			break;

			case IN_L_KICK:
			{
				/*
				if (isOnLeft){
				c_punch1 = App->colision->AddCollider({ position.x + 10, position.y - 75, 40, 10 }, COLLIDER_PUNCH_1, this);
				}
				else{
				c_punch1 = App->colision->AddCollider({ position.x - 50, position.y - 75, 40, 10 }, COLLIDER_PUNCH_1, this);
				}
				*/
				isCrouchKicking = true;
				App->audio->PlayFx(normalFX);
				state = ST_KICK_CROUCH;
			}
			break;

			case IN_CROUCH_UP: state = ST_IDLE; collider->rect.h = 90; isCrouching = false; break;
			
			}
		}
		break;

		case ST_PUNCH_CROUCH:
		{
			if (last_input == IN_CROUCH_UP)
			{
				isCrouching = false;
			}
			switch (last_input)
			{
			case IN_PUNCH_CROUCH_FINISH: 
				c_punch1->to_delete = true;
				if (isCrouching)
				{
					state = ST_CROUCHED;
				}
				if (!isCrouching)
				{
					state = ST_IDLE;
				}
				break;
			}
		}
		break;

		case ST_KICK_CROUCH:
		{
			if (last_input == IN_CROUCH_UP)
			{
				isCrouching = false;
			}
			switch (last_input)
			{
			case IN_KICK_CROUCH_FINISH: 
				/*c_punch1->to_delete = true;  state = ST_IDLE;*/ 
				if (isCrouching)
				{
					state = ST_CROUCHED;
				}
				if (!isCrouching)
				{
					state = ST_IDLE;
				}
				break;
			}
		}
		break;

		case ST_PUNCH_JUMP:
		{
			switch (last_input)
			{
			case IN_JUMP_N_FINISH:
				isFalling = isJumping = false;
				state = ST_IDLE;
				break;
			//case IN_PUNCH_JUMP_FINISH:
				/*c_punch1->to_delete = true;  state = ST_IDLE;*/
				//state = ST_JUMPING_NEUTRAL;
				//break;
			}
		}
		break;

		case ST_KICK_JUMP:
		{
			switch (last_input)
			{
			case IN_JUMP_N_FINISH:
				isFalling = isJumping = false;
				state = ST_IDLE;
				break;
				
			//case IN_KICK_JUMP_FINISH:
				/*c_punch1->to_delete = true;  state = ST_IDLE;*/
				//state = ST_JUMPING_NEUTRAL;
				//break;
				
			}
		}
		break;
		}
	}
	return state;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	current_animation = &idle;

	current_state = ST_UNKNOWN;

	p1_states state = App->player->process_fsm(inputs);

		if (state != current_state)
		{
			switch (state)
			{
			case ST_IDLE:
				if (!doDefense)
				{
					c_defense->type = COLLIDER_NONE;
				}
				collider->rect.h = 90;
				break;
			case ST_HIT:
			
				break;

			case ST_WALK_RIGHT:
			{
				if (!isOnLeft && App->player2->isAttacking)
				{
					doDefense = true;
				}

				else
				{
					doDefense = false;
				}

				if (position.x < 860.0 && position.x < (App->renderer->OpCamera.x) + SCREEN_WIDTH && !doDefense)
				{
					if (position.x < App->player2->position.x)
						current_animation = &forward;
					else 
						current_animation = &backward;
					position.x += speed;
					collider->SetPos(position.x - 30, position.y - 90);
				}

				if (doDefense)
				{
					current_animation = &block;

					c_defense->type = COLLIDER_DEFENSE_1;
					doDefense = false;
				}
			}
			break;
			case ST_WALK_LEFT:
			{
				if (isOnLeft && App->player2->isAttacking)
				{
					doDefense = true;
				}

				else
				{
					doDefense = false;
				}

				if (position.x > 0.0 && position.x > (App->renderer->OpCamera.x) + 20 && !doDefense)
				{
					if (position.x > App->player2->position.x)
						current_animation = &forward;
					else
						current_animation = &backward;
					position.x -= speed;
					collider->SetPos(position.x - 30, position.y - 90);
				}

				if (doDefense)
				{
					current_animation = &block;

					c_defense->type = COLLIDER_DEFENSE_1;
				}
			}
			break;
			case ST_JUMPING_NEUTRAL:
			if (!isFalling)
			{
				current_animation = &jump;
				//current_animation = &idle;
				position.y -= 5.0f ;
				/*
				collider->rect.h = 90;
				collider->SetPos(position.x - 30, position.y + 90);

				*/
			}
			else
			{
				position.y += 5.0f;
				if (!isAttacking)
				{

					current_animation = &jumpfalling;
					
				}
			}
			collider->rect.h = 90;
			break;

			case ST_JUMP_FORWARD:
			if (!isFalling)
			{
				current_animation = &jumpforward;
				//current_animation = &idle;
				position.y -= 5.0f;
				/*
				collider->rect.h = 90;
				collider->SetPos(position.x - 30, position.y + 90);

				*/
			}
			else
			{
				position.y += 5.0f;
				if (!isAttacking)
				{

					current_animation = &jumpforwardfalling;

				}
			}

			if (isGoingRight)
			{
				if (position.x < 860.0 && position.x < (App->renderer->OpCamera.x) + SCREEN_WIDTH && !doDefense)
				{
					position.x += speed;
				}
			}

			if (isGoingLeft)
			{
				if (position.x > 0.0 && position.x >(App->renderer->OpCamera.x) + 20 && !doDefense)
				{
					position.x -= speed;
				}
			}

			collider->rect.h = 90;
			break;

			case ST_JUMP_BACKWARD:
			if (!isFalling)
			{
				current_animation = &jumpbackward;
				//current_animation = &idle;
				position.y -= 5.0f;
				/*
				collider->rect.h = 90;
				collider->SetPos(position.x - 30, position.y + 90);

				*/
			}
			else
			{
				position.y += 5.0f;
				if (!isAttacking)
				{

					current_animation = &jumpbackwardfalling;

				}
			}

			if (isGoingRight)
			{
				if (position.x < 860.0 && position.x < (App->renderer->OpCamera.x) + SCREEN_WIDTH && !doDefense)
				{
					position.x += speed;
				}
			}

			if (isGoingLeft)
			{
				if (position.x > 0.0 && position.x >(App->renderer->OpCamera.x) + 20 && !doDefense)
				{
					position.x -= speed;
				}
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

			case ST_PUNCH_CROUCH:
				current_animation = &crouchpunch;
				break;

			case ST_KICK_CROUCH:
				current_animation = &crouchkick;
				break;

			case ST_PUNCH_JUMP:
				if (!isFalling)
				{
					position.y -= 5.0f;
					/*
					collider->rect.h = 90;
					collider->SetPos(position.x - 30, position.y + 90);
					*/
				}
				else
				{
					position.y += 5.0f;
				}

				if (isJumpingF)
				{
					if (isGoingRight)
					{
						if (position.x < 860.0 && position.x < (App->renderer->OpCamera.x) + SCREEN_WIDTH && !doDefense)
						{
							position.x += speed;
						}
					}

					if (isGoingLeft)
					{
						if (position.x > 0.0 && position.x >(App->renderer->OpCamera.x) + 20 && !doDefense)
						{
							position.x -= speed;
						}
					}
				}

				if (isJumpingB)
				{
					if (isGoingRight)
					{
						if (position.x < 860.0 && position.x < (App->renderer->OpCamera.x) + SCREEN_WIDTH && !doDefense)
						{
							position.x += speed;
						}
					}

					if (isGoingLeft)
					{
						if (position.x > 0.0 && position.x >(App->renderer->OpCamera.x) + 20 && !doDefense)
						{
							position.x -= speed;
						}
					}
				}

				collider->rect.h = 90;
				current_animation = &jumppunch;
				break;

			case ST_KICK_JUMP:
				if (!isFalling)
				{
					position.y -= 5.0f;
					/*
					collider->rect.h = 90;
					collider->SetPos(position.x - 30, position.y + 90);
					*/
				}
				else
				{
					position.y += 5.0f;
				}

				if (isJumpingF)
				{
					if (isGoingRight)
					{
						if (position.x < 860.0 && position.x < (App->renderer->OpCamera.x) + SCREEN_WIDTH && !doDefense)
						{
							position.x += speed;
						}
					}

					if (isGoingLeft)
					{
						if (position.x > 0.0 && position.x >(App->renderer->OpCamera.x) + 20 && !doDefense)
						{
							position.x -= speed;
						}
					}
				}

				else if (isJumpingB)
				{
					if (isGoingRight)
					{
						if (position.x < 860.0 && position.x < (App->renderer->OpCamera.x) + SCREEN_WIDTH && !doDefense)
						{
							position.x += speed;
						}
					}

					if (isGoingLeft)
					{
						if (position.x > 0.0 && position.x >(App->renderer->OpCamera.x) + 20 && !doDefense)
						{
							position.x -= speed;
						}
					}
				}

				collider->rect.h = 90;
				current_animation = &jumpkick;
				break;
			}
		}

		/**
		*TODO: COLISIO BONA
		**/
		

		c_defense->SetPos(position.x - 30, position.y - 90);
		collider->SetPos(position.x - 30, position.y - 90);
		
		if (isJumping)
		{
			c_defense->SetPos(position.x - 30, position.y - 150);
			collider->SetPos(position.x - 30, position.y - 150);
		}

		if (isFalling)
		{
			c_defense->SetPos(position.x - 30, position.y - 90);
			collider->SetPos(position.x - 30, position.y - 90);

		}
		if (isCrouching)
		{
			collider->SetPos(position.x - 30, position.y - 60);
			c_defense->SetPos(position.x - 30, position.y - 60);
		}

		current_state = state;
		App->player->internal_input(inputs);
		

	//Checks where player is facing
	if (App->player->position.x < App->player2->position.x)
		isOnLeft = true;
	else
		isOnLeft = false;

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	App->renderer->Blit(graphics, position.x - 35, 208, &shadow, 1.0f);
	App->renderer->Blit(graphics, position.x - (r.w / 2.0f), position.y - r.h, &r, 1.0f, isOnLeft);
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (App->player2->doDefense == false)
		App->player2->Health--;
}


