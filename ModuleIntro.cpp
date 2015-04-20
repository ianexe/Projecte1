#include "ModuleIntro.h"

ModuleIntro::ModuleIntro(Application* app, bool start_enabled) : Module(app, start_enabled);
{
	App->renderer->camera.x = App->renderer->camera.x = 0.0;
}


update_status ModuleIntro::Update()
{
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->intro, App->scene_ken, FADE_TIME);
	}
}