#include "Globals.h"
#include "Application.h"
#include "ModuleIntro.h"

ModuleIntro::ModuleIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	isEnd = false;

	warning.frames.PushBack({ 680, 11, 417, 196 });
	warning.frames.PushBack({ 889, 218, 314, 197 });

	warning.speed = 0.01;

	intro.frames.PushBack({ 71, 323, 254, 189 });
	intro.frames.PushBack({ 335, 87, 254, 189 });
	intro.frames.PushBack({ 335, 80, 254, 189 });
	intro.frames.PushBack({ 335, 70, 254, 189 });
	intro.frames.PushBack({ 335, 60, 254, 189 });
	intro.frames.PushBack({ 335, 50, 254, 189 });
	intro.frames.PushBack({ 335, 40, 254, 189 });
	intro.frames.PushBack({ 335, 30, 254, 189 });
	intro.frames.PushBack({ 335, 20, 254, 189 });
	intro.frames.PushBack({ 335, 10, 254, 189 });
	intro.frames.PushBack({ 335, 0, 254, 189 });
	intro.frames.PushBack({ 71, 200, 254, 189 });
	intro.frames.PushBack({ 71, 185, 254, 189 });
	intro.frames.PushBack({ 71, 163, 254, 189 });
	intro.frames.PushBack({ 71, 141, 254, 189 });
	intro.frames.PushBack({ 71, 119, 254, 189 });
	intro.frames.PushBack({ 71, 90, 254, 189 });
	intro.frames.PushBack({ 71, 90, 254, 189 });
	intro.frames.PushBack({ 71, 90, 254, 189 });

	intro.speed = 0.07f;

	insert_coin.frames.PushBack({ 335, 289, 254, 189 });
	insert_coin.frames.PushBack({ 609, 289, 254, 189 });
	insert_coin.frames.PushBack({ 335, 289, 254, 189 });
	insert_coin.frames.PushBack({ 609, 289, 254, 189 });

	insert_coin.speed = 0.04f;

}

bool ModuleIntro::Start()
{
	LOG("Loading Intro scene");
	music_on = true;

	graphics = App->textures->Load("intro_def.png");

	
	music_coin = App->audio->LoadFx("coin.wav");

	return true;
}
update_status ModuleIntro::PreUpdate()
{

	
	//App->renderer->Blit(graphics, 0, 0,&scroll);
	return UPDATE_CONTINUE;
}

update_status ModuleIntro::Update()
{
	
	Animation* current_animation = &warning;

	if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
	{
		
		if (music_on){

			App->audio->PlayMusic("opening.ogg", FADE_TIME);
			music_on = false;
		}
		
		current_animation = &intro;

		if (current_animation->getFrame() >= current_animation->frames.Count() - current_animation->speed)
		{
			//App->fade->FadeToBlack(App->scene_intro, App->scene_ken, FADE_TIME);
			current_animation = &insert_coin;

		}
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		App->audio->PlayFx(music_coin);
//		App->fade->FadeToBlack(App->scene_intro, App->map, FADE_TIME);
	}

	scroll = current_animation->GetCurrentFrame();

	if (current_animation == &warning){

		App->renderer->Blit(graphics, 40, -10, &scroll, 0.01f);
	}

	else{
		App->renderer->Blit(graphics, 60, 10, &scroll, 0.01f);
	}


	return UPDATE_CONTINUE;
}

bool ModuleIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(graphics);

	return true;
}