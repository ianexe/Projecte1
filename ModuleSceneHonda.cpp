#include "Globals.h"
#include "Application.h"
#include "ModuleSceneHonda.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneHonda::ModuleSceneHonda(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	// ground
	ground = {8, 376, 848, 64};

	// roof
	roof = {91, 7, 765, 49};

	// foreground
	foreground = {164, 66, 336, 51};

	// Background / sky
	background = {120, 128, 671, 199};

	// flag animation
	water.frames.PushBack({8, 447, 283, 9});
	water.frames.PushBack({296, 447, 283, 12});
	water.frames.PushBack({588, 447, 283, 18});
	water.speed = 0.02f;
}

ModuleSceneHonda::~ModuleSceneHonda()
{}

// Load assets
bool ModuleSceneHonda::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("honda_stage2.png");
	App->player->Enable();
	App->player2->Enable();
	App->audio->PlayMusic("honda.ogg", FADE_TIME);

	return ret;
}

// Load assets
bool ModuleSceneHonda::CleanUp()
{
	LOG("Unloading honda stage");

	App->textures->Unload(graphics);
	App->player->Disable();
	App->player2->Disable();
	return true;
}

// Update: draw background
update_status ModuleSceneHonda::Update()
{
	// Draw everything --------------------------------------	
	App->renderer->Blit(graphics, 0, 160, &ground);
	App->renderer->Blit(graphics, 50, -15, &background, 0.75f); // back of the room
	
	App->renderer->Blit(graphics, 280, 125, &foreground);
	App->renderer->Blit(graphics, 305, 136, &(water.GetCurrentFrame())); // water animation
	App->renderer->Blit(graphics, 0, -16, &roof, 0.75f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_honda, App->scene_ken, FADE_TIME);
	}
	

	return UPDATE_CONTINUE;
}