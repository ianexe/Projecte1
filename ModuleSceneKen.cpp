#include "Globals.h"
#include "Application.h"
#include "ModuleSceneKen.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneKen::ModuleSceneKen(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// foreground
	foreground.x = 8;
	foreground.y = 24;
	foreground.w = 521;
	foreground.h = 181;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.frames.PushBack({848, 208, 40, 40});
	flag.frames.PushBack({848, 256, 40, 40});
	flag.frames.PushBack({848, 304, 40, 40});
	flag.speed = 0.08f;

	// Girl Animation
	girl.frames.PushBack({624, 16, 32, 56});
	girl.frames.PushBack({624, 80, 32, 56});
	girl.frames.PushBack({624, 144, 32, 56});
	girl.speed = 0.05f;

	// HatGuy Animation
	hatGuy.frames.PushBack({ 760, 16, 40, 40 });
	hatGuy.frames.PushBack({ 760, 64, 40, 40 });
	hatGuy.frames.PushBack({ 760, 112, 40, 40 });
	hatGuy.speed = 0.08f;

	// for moving the foreground
	foreground_pos = 0;
	forward = true;

	/*
	// Life Bar
	lifebar.x = 31;
	lifebar.y = 18;
	lifebar.w = 322;
	lifebar.h = 14;
	*/
}

ModuleSceneKen::~ModuleSceneKen()
{}

// Load assets
bool ModuleSceneKen::Start()
{
	LOG("Loading ken scene");
	
	graphics = App->textures->Load("ken_stage.png");
	App->colision->Enable();
	App->player->Enable();
	App->player2->Enable();
	App->ui->Enable();
	
	App->audio->PlayMusic("ken.ogg",FADE_TIME);
	
	return true;
}

// UnLoad assets
bool ModuleSceneKen::CleanUp()
{
	LOG("Unloading ken scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	App->player2->Disable();
	App->colision->Disable();
	App->ui->Disable();
	return true;
}

// Update: draw background
update_status ModuleSceneKen::Update()
{
	// Calculate boat Y position -----------------------------
	
	if (foreground_pos < -6.0f)
		forward = false;
	else if (foreground_pos > 0.0f)
		forward = true;

	if (forward)
		foreground_pos -= 0.02f;
	else
		foreground_pos += 0.02f;

	//Prova meva per fer el codi Calculate boat Y position
	/*for (forward == true; foreground_pos < -6.0f; foreground_pos -= 0.02f);
	forward = false;
	for (forward == false; foreground_pos < 0.0f; foreground_pos += 0.02f);
	forward = true;*/
	
	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky
	App->renderer->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	App->renderer->Blit(graphics, 0, foreground_pos, &foreground, 0.92f);
	App->renderer->Blit(graphics, 192, 105 + foreground_pos, &(girl.GetCurrentFrame()), 0.92f); // girl animation
	App->renderer->Blit(graphics, 87, 25 + foreground_pos, &(hatGuy.GetCurrentFrame()), 0.92f); //Hat guy animation
	App->renderer->Blit(graphics, 0, 170, &ground);
	//App->renderer->Blit(ui, 31, 18, &lifebar);
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == 1)
	{
		//App->fade->FadeToBlack(App->scene_ken, App->scene_honda, FADE_TIME);
	}

	if (App->player->Health <= 0 || App->player2->Health <= 0)
	{
		App->fade->FadeToBlack(App->scene_ken, App->scene_intro, FADE_TIME);
	}

	
	return UPDATE_CONTINUE;
}