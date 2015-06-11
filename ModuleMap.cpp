#include "Globals.h"
#include "Application.h"
#include "ModuleMap.h"

ModuleMap::ModuleMap(Application* app, bool start_enabled) : Module(app, start_enabled)
{


	countdown.frames.PushBack({ 335, 289, 254, 189 });
	countdown.frames.PushBack({ 335, 289, 254, 189 });
	countdown.frames.PushBack({ 335, 289, 254, 189 });


	countdown.speed = 0.04f;

}

bool ModuleMap::Start()
{
	LOG("Loading Intro scene");

	scroll = { 0, 0, 600, 600 };

	map_selection = App->textures->Load("characters.png");
	versus_image = App->textures->Load("characters.png");

	App->audio->PlayMusic("opening.ogg", FADE_TIME);

	return true;
}
update_status ModuleMap::PreUpdate()
{


	//App->renderer->Blit(graphics, 0, 0,&scroll);
	return UPDATE_CONTINUE;
}

update_status ModuleMap::Update()
{
	App->renderer->Blit(map_selection, 100, 100, &scroll);
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		start_time = SDL_GetTicks();

		while (SDL_GetTicks() - start_time < 200){

			scroll = countdown.GetCurrentFrame();

			App->renderer->Blit(versus_image, 0, 0, &scroll);


			if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
			{
				App->fade->FadeToBlack(App->map, App->scene_ken, FADE_TIME);
			}

		}

		App->fade->FadeToBlack(App->map, App->scene_ken, FADE_TIME);
		
	}
	
	return UPDATE_CONTINUE;
}

bool ModuleMap::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(map_selection);
	App->textures->Unload(versus_image);

	return true;
}