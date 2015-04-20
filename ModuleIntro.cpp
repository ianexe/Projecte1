#include "Globals.h"
#include "Application.h"
#include "ModuleIntro.h"
ModuleIntro::ModuleIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	App->renderer->camera.x = App->renderer->camera.x = 0.0;
	scroll = NULL;
}

bool ModuleIntro::Start()
{
	LOG("Loading Intro scene");

	scroll = App->textures->Load("intro_def.png");
	//App->audio->PlayMusic("ken.ogg", FADE_TIME);
	isEnd = false;
	return true;
}
update_status ModuleIntro::PreUpdate()
{
	App->renderer->camera.y -= 3;
	App->renderer->Blit(scroll, 0, 0, NULL);
	return UPDATE_CONTINUE;
}

update_status ModuleIntro::Update()
{ 
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_intro, App->scene_ken, FADE_TIME);
	}
	return UPDATE_CONTINUE;
}

bool ModuleIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(scroll); 
		return true;
}