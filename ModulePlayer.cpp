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



}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	Health = 100;

	graphics = App->textures->Load("ryu4.png"); // arcade version
	collider = App->colision->AddCollider({ position.x, position.y, 60, 90 }, COLLIDER_NEUTRAL_1);
	c_defense = App->colision->AddCollider({ position.x + 5, position.y + 10, 60, 40 }, COLLIDER_NONE);


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

// Update: draw background
update_status ModulePlayer::Update()
{

	Animation* current_animation = &idle;
	c_defense->type = COLLIDER_NONE;
	collider->rect.h = 90;

	collider->SetPos(position.x - 30, position.y - 90);
	c_defense->SetPos(position.x - 30, position.y - 90);

	// debug camera movement --------------------------------



	float speed = 3;

	if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && (!isAttacking))
	{


		if (App->player->position.x > 0.0 && App->player->position.x > (App->renderer->OpCamera.x) + 20)
		{

			if (isOnLeft){

				c_defense->type = COLLIDER_DEFENSE_1;
				collider->rect.h = 50;
				collider->SetPos(position.x - 30, position.y - 50);
			}
			else{
				c_defense->type = COLLIDER_NONE;
				collider->rect.h = 90;
				collider->SetPos(position.x - 30, position.y - 90);
			}

			current_animation = &forward;
			position.x -= speed;


			c_defense->SetPos(position.x - 27, position.y - 90);


		}
	}

	else if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && (!isAttacking))
	{
		if (App->player->position.x < 896.0 && App->player->position.x < (App->renderer->OpCamera.x) + SCREEN_WIDTH)
		{
			if (isOnLeft){

				c_defense->type = COLLIDER_NONE;
				collider->rect.h = 90;
				collider->SetPos(position.x - 30, position.y - 90);
			}
			else{
				c_defense->type = COLLIDER_DEFENSE_1;
				collider->rect.h = 50;
				collider->SetPos(position.x - 30, position.y - 50);
			}

			current_animation = &forward;
			position.x += speed;


			c_defense->SetPos(position.x - 27, position.y - 90);

		}
	}

	if ((App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN) && (!isAttacking))
	{
		doPunch = true;
		isAttacking = true;
		c_defense->type = COLLIDER_NONE;
		collider->rect.h = 90;
		if (isOnLeft){

			c_punch1 = App->colision->AddCollider({ position.x + 10, position.y - 75, 50, 10 }, COLLIDER_PUNCH_1, this);

		}
		else{
			c_punch1 = App->colision->AddCollider({ position.x - 60, position.y - 75, 50, 10 }, COLLIDER_PUNCH_1, this);
		}


	}

	if ((App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN) && (!isAttacking))
	{
		doPunch2 = true;
		isAttacking = true;
		c_defense->type = COLLIDER_NONE;
		collider->rect.h = 90;
		if (isOnLeft){
			c_punch2 = App->colision->AddCollider({ position.x + 10, position.y - 77, 50, 10 }, COLLIDER_PUNCH_1, this);
		}
		else
		{
			c_punch2 = App->colision->AddCollider({ position.x - 60, position.y - 77, 50, 10 }, COLLIDER_PUNCH_1, this);
		}

	}

	if ((App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN) && (!isAttacking))
	{
		doKick = true;
		isAttacking = true;
		c_defense->type = COLLIDER_NONE;
		collider->rect.h = 90;
		if (isOnLeft){
			c_kick = App->colision->AddCollider({ position.x + 7, position.y - 92, 50, 50 }, COLLIDER_KICK_1, this);
		}
		else{
			c_kick = App->colision->AddCollider({ position.x - 57, position.y - 92, 50, 50 }, COLLIDER_KICK_1, this);
		}


	}

	//Does attack if called

	if (doPunch)
	{
		current_animation = &punch;


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


	if (App->player->position.x < App->player2->position.x)
		isOnLeft = true;
	else
		isOnLeft = false;

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->renderer->Blit(graphics, position.x - (r.w / 2.0f), position.y - r.h, &r, 1.0f, isOnLeft);


	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	App->player2->Health--;
}