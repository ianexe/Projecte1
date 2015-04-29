#include "Globals.h"
#include "Application.h"
#include "ModuleIntro.h"
ModuleIntro::ModuleIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	scroll.x = -48;
	scroll.y = 0;
	graphics = NULL;
	scroll.w = SCREEN_WIDTH;
	scroll.h = SCREEN_HEIGHT;
	isEnd = false;
}

bool ModuleIntro::Start()
{
	LOG("Loading Intro scene");
	
	
	graphics = App->textures->Load("intro_end.png");

	App->audio->PlayMusic("opening.ogg", FADE_TIME);
	
	return true;
}
update_status ModuleIntro::PreUpdate()
{
	
	
	App->renderer->Blit(graphics, 0, 0,&scroll);
	return UPDATE_CONTINUE;
}

update_status ModuleIntro::Update()
{ 
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		App->fade->FadeToBlack(App->scene_intro, App->scene_ken, FADE_TIME);
	}
	return UPDATE_CONTINUE;
}

bool ModuleIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(graphics); 
		return true;
}