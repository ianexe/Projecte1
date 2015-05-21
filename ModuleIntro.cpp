#include "Globals.h"
#include "Application.h"
#include "ModuleIntro.h"

ModuleIntro::ModuleIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	isEnd = false;

	intro.frames.PushBack({ 71, 323, 254, 189 });
	intro.frames.PushBack({ 335, 87, 254, 189 });
	intro.frames.PushBack({ 335, 60, 254, 189 });
	intro.frames.PushBack({ 335, 40, 254, 189 });
	intro.frames.PushBack({ 71, 200, 254, 189 });
	intro.frames.PushBack({ 71, 185, 254, 189 });
	intro.frames.PushBack({ 71, 163, 254, 189 });
	intro.frames.PushBack({ 71, 141, 254, 189 });
	intro.frames.PushBack({ 71, 119, 254, 189 });
	intro.frames.PushBack({ 71, 90, 254, 189 });	

	intro.speed = 0.05f;

	insert_coin.frames.PushBack({ 335, 289, 254, 189 });
	insert_coin.frames.PushBack({ 609, 289, 254, 189 });
	insert_coin.frames.PushBack({ 335, 289, 254, 189 });
	insert_coin.frames.PushBack({ 609, 289, 254, 189 });

	insert_coin.speed = 0.04f;

}

bool ModuleIntro::Start()
{
	LOG("Loading Intro scene");
	
	
	intro_animation = App->textures->Load("intro_end.png");
	graphics = App->textures->Load("intro_def.png");
	
	App->audio->PlayMusic("opening.ogg", FADE_TIME);
	
	return true;
}
update_status ModuleIntro::PreUpdate()
{
	
	//App->renderer->Blit(graphics, 0, 0,&scroll);
	return UPDATE_CONTINUE;
}

update_status ModuleIntro::Update()
{ 
	
	Animation* current_animation = &intro;


	if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
	{
		//App->fade->FadeToBlack(App->scene_intro, App->scene_ken, FADE_TIME);
		current_animation = &insert_coin;
		
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		App->fade->FadeToBlack(App->scene_intro, App->scene_ken, FADE_TIME);
	}

	scroll = current_animation->GetCurrentFrame();

	App->renderer->Blit(graphics, 60, 10, &scroll, 0.01f);

	return UPDATE_CONTINUE;
}

bool ModuleIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(graphics);
	App->textures->Unload(intro_animation);
	return true;
}