#include "Application.h"
#include "ModuleUI.h"
#include "Globals.h"

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	// Life Bar
	lifebar.x = 31;
	lifebar.y = 18;
	lifebar.w = 322;
	lifebar.h = 14;

	x = 31;
	y = 18;
}


ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Start()
{
	graphics = App->textures->Load("ui.png");
	return true;
}

bool ModuleUI::CleanUp()
{
	App->textures->Unload(graphics);
	return true;
}

update_status ModuleUI::Update()
{
	App->renderer->Blit(graphics, x, y, &lifebar);
	return UPDATE_CONTINUE;
}

