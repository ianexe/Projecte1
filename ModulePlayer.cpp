#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	position.x = 80;
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

	Health = 100;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ryu4.png"); // arcade version
	collider = App->colision->AddCollider({ position.x, position.y, 60, 90 }, COLLIDER_NEUTRAL_1);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	//App->player_col->CleanUp();
	//App->player_col->PreUpdate();

	//width_col = 35;
	//height_col = 85;

	Animation* current_animation = &idle;

	/*if (isOnLeft){

		
		App->player_col->Init_rec(detection, App->player->position.x - 20, (App->player->position.y) - 90, width_col, height_col);
	}
	else{

		App->player_col->Init_rec(detection, App->player->position.x - 20, (App->player->position.y) - 90, width_col, height_col);
	}*/
	//App->player_col->AddCollider(detection, COLLIDER_NEUTRAL_1, NULL);
	
	collider->SetPos(position.x - 20, position.y - 90);
	
	
	
	// debug camera movement --------------------------------


	
	float speed = 3;

	if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && (!isAttacking))
	{
		if (App->player->position.x > 0.0 && App->player->position.x > (App->renderer->OpCamera.x) + 20)
		{
			width_col = 35;
			height_col = 85;

			current_animation = &forward;
			position.x -= speed;

			collider->SetPos(position.x - 20, position.y - 90);

		}
	}

	else if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && (!isAttacking))
	{
		if (App->player->position.x < 896.0 && App->player->position.x < (App->renderer->OpCamera.x) + SCREEN_WIDTH)
		{
			width_col = 35;
			height_col = 85;

			current_animation = &forward;
			position.x += speed;
			
			collider->SetPos(position.x - 20, position.y - 90);
			//App->player_col->AddCollider(detection, COLLIDER_NEUTRAL_1, NULL);
		}
	}

	if ((App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN) && (!isAttacking))
	{
		doPunch = true;
		isAttacking = true;
		if (isOnLeft){

			c_punch1 = App->colision->AddCollider({ position.x + 10, position.y - 75, 50, 10 }, COLLIDER_PUNCH_1, NULL);
			//collider->SetPos(position.x + 10, position.y - 75);

		}
		else{
			c_punch1 = App->colision->AddCollider({ position.x - 60, position.y - 75, 50, 10 }, COLLIDER_PUNCH_1, NULL);
		}

	
	}

	if ((App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN) && (!isAttacking))
	{
		doPunch2 = true;
		isAttacking = true;
		if (isOnLeft){
			c_punch2 = App->colision->AddCollider({ position.x + 10, position.y - 77, 50, 10 }, COLLIDER_PUNCH_1, NULL);
		}
		else
		{
			c_punch2 = App->colision->AddCollider({ position.x - 60, position.y - 77, 50, 10 }, COLLIDER_PUNCH_1, NULL);
		}
		
	}

	if ((App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN) && (!isAttacking))
	{
		doKick = true;
		isAttacking = true;
		if (isOnLeft){
			c_kick = App->colision->AddCollider({ position.x + 7, position.y - 92, 50, 50 }, COLLIDER_KICK_1, NULL);
		}
		else{
			c_kick = App->colision->AddCollider({ position.x - 57, position.y - 92, 50, 30 }, COLLIDER_KICK_1, NULL);
		}

		
	}

	//Does attack if called

	if (doPunch)
	{
		current_animation = &punch;
		width_col = 50;
		height_col = 10;

		
		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			doPunch = false;
			isAttacking = false;
			c_punch1->to_delete = true;
		}
	}


	if (doPunch2)
	{
		current_animation = &punch2;
		width_col = 50;
		height_col = 10;

		
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
		width_col = 50;
		height_col = 30;

		//App->player_col->AddCollider(atac, COLLIDER_KICK_1, NULL);

		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			doKick = false;
			isAttacking = false;
			c_kick->to_delete = true;
		}
	}

	//Checks where player is facing

	if (App->player->position.x < App->player2->position.x)
		isOnLeft = true;
	else
		isOnLeft = false;

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->renderer->Blit(graphics, position.x - (r.w / 2.0f), position.y - r.h, &r, 1.0f, isOnLeft);


	//Comprovacio mala
	/*
	//App->player_col->Update();

	if (App->player_col->check_collision == true){

		App->fade->FadeToBlack(App->scene_ken, App->scene_honda, FADE_TIME);
		App->player_col->check_collision = false;
	}*/

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	assert(1 == 1);
	App->player->Health -= 50;
}