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

	position.x = 31;
	position.y = 18;

	// Life 1
	life1.x = 0;
	life1.y = 0;
	life1.w = life1X = 144;
	life1.h = 9;

	// Life 2
	life2.x = 0;
	life2.y = 0;
	life2.w = life2X = 144;
	life2.h = 9;
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
	life1X = App->player->Health;
	life2X = App->player2->Health;

	life1.w = life1X;
	life2.w = life2X;

	App->renderer->Blit(graphics, App->renderer->OpCamera.x + position.x, position.y, &lifebar);
	App->renderer->Blit(graphics, App->renderer->OpCamera.x + position.x + 145 - life1.w, position.y + 3, &life1);
	App->renderer->Blit(graphics, App->renderer->OpCamera.x + position.x + 177, position.y + 3, &life2);
	return UPDATE_CONTINUE;
}

