#include "Globals.h"
#include "Application.h"
#include "ModuleIntro.h"
ModuleIntro::ModuleIntro(Application* app, bool start_enabled) : Module(app, start_enabled);
{
	App->renderer->camera.x = App->renderer->camera.x = 0.0;
	graphics = NULL;

	backgorund.x = 0;
	background
}


update_status ModuleIntro::Update()
{
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_intro, App->scene_ken, FADE_TIME);
	}
}