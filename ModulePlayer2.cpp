#include "Globals.h"
#include "Application.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	width_col = 0;
	height_col = 0;
	position.x = 380.0;
	position.y = 216.0;

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

	graphics = App->textures->Load("ryu4.png"); // arcade version

	return true;
}

// Unload assets
bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer2::Update()
{
	
	App->player2_col->CleanUp();
	App->player2_col->PreUpdate();
	
	width_col = 35;
	height_col = 85;
	
	Animation* current_animation = &idle;

	if (isOnLeft){

		App->player2_col->Init_rec(detection, App->player2->position.x - 20, (App->player2->position.y) - 90, width_col, height_col);
	}
	else{

		App->player2_col->Init_rec(detection, App->player2->position.x - 20, (App->player2->position.y) - 90, width_col, height_col);
	}

	App->player2_col->AddCollider(detection, COLLIDER_NEUTRAL_2, NULL);

	// debug camera movement --------------------------------
	
	
	int speed = 3;

	if ((App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) && (!isAttacking))
	{
		if (position.x > 0.0 && position.x > (App->renderer->OpCamera.x) + 10)
		{
			width_col = 35;
			height_col = 85;

			current_animation = &forward;
			position.x -= speed;

			if (isOnLeft){

				App->player2_col->Init_rec(detection, App->player2->position.x - 20, (App->player2->position.y) - 90, width_col, height_col);
			}
			else{

				App->player2_col->Init_rec(detection, App->player2->position.x - 20, (App->player2->position.y) - 90, width_col, height_col);
			}

			App->player2_col->AddCollider(detection, COLLIDER_NEUTRAL_2, NULL);

		}
	}

	if ((App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) && (!isAttacking))
	{
		if (position.x < 896.0 && position.x < (App->renderer->OpCamera.x) + SCREEN_WIDTH)
		{
				width_col = 35;
				height_col = 85;

				current_animation = &forward;
				position.x += speed;

				if (isOnLeft){

					App->player2_col->Init_rec(detection, App->player2->position.x - 20, (App->player2->position.y) - 90, width_col, height_col);
				}
				else{

					App->player2_col->Init_rec(detection, App->player2->position.x - 20, (App->player2->position.y) - 90, width_col, height_col);
				}

				App->player2_col->AddCollider(detection, COLLIDER_NEUTRAL_2, NULL);


			}
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
	}

	if ((App->input->GetKey(SDL_SCANCODE_KP_3) == KEY_DOWN) && (!isAttacking))
	{
		doKick = true;
		isAttacking = true;
	}

	//Does attack if called

	if (doPunch)
	{
		current_animation = &punch;
		width_col = 50;
		height_col = 10;

		if (isOnLeft){

			App->player2_col->Init_rec(atac, App->player2->position.x + 10, (App->player2->position.y) - 75, width_col, height_col);
		}
		else{

			App->player2_col->Init_rec(atac, App->player2->position.x - 60, (App->player2->position.y) - 75, width_col, height_col);
		}

		App->player2_col->AddCollider(atac, COLLIDER_PUNCH_2, NULL);

		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			doPunch = false;
			isAttacking = false;
		}
	}


	if (doPunch2)
	{
		current_animation = &punch2;
		width_col = 50;
		height_col = 10;


		if (isOnLeft){

			App->player2_col->Init_rec(atac, App->player2->position.x + 10, (App->player2->position.y) - 77, width_col, height_col);
		}
		else{

			App->player2_col->Init_rec(atac, App->player2->position.x - 60, (App->player2->position.y) - 77, width_col, height_col);
		}

		App->player2_col->AddCollider(atac, COLLIDER_PUNCH_2, NULL);

		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			doPunch2 = false;
			isAttacking = false;
		}
	}

	if (doKick)
	{
		current_animation = &kick;
		width_col = 50;
		height_col = 30;


		if (isOnLeft){

			App->player2_col->Init_rec(atac, App->player2->position.x + 7, (App->player2->position.y) - 92, width_col, height_col);
		}
		else{

			App->player2_col->Init_rec(atac, App->player2->position.x - 57, (App->player2->position.y) - 92, width_col, height_col);
		}

		App->player2_col->AddCollider(atac, COLLIDER_KICK_2, NULL);

		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			doKick = false;
			isAttacking = false;
		}
	}

	//Checks where player is facing

	if (App->player->position.x > App->player2->position.x)
		isOnLeft = true;
	else
		isOnLeft = false;

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->renderer->Blit(graphics, position.x - (r.w / 2.0f), position.y - r.h, &r, 1.0f, isOnLeft);

	App->player2_col->Update();
	
	if (App->player2_col->check_collision == true){

		App->fade->FadeToBlack(App->scene_ken, App->scene_honda, FADE_TIME);
		App->player2_col->check_collision = false;
	}

	return UPDATE_CONTINUE;
}