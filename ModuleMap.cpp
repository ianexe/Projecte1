#include "Globals.h"
#include "Application.h"
#include "ModuleMap.h"

ModuleMap::ModuleMap(Application* app, bool start_enabled) : Module(app, start_enabled)
{


	countdown.frames.PushBack({ 452, 852, 384, 226 });
	countdown.frames.PushBack({ 860, 586, 385, 225 });
	countdown.frames.PushBack({ 450, 584, 385, 226 });
	countdown.frames.PushBack({ 42, 578, 386, 225 });
	countdown.frames.PushBack({ 858, 316, 385, 225 });
	countdown.frames.PushBack({ 450, 314, 384, 225 });
	countdown.frames.PushBack({ 42, 312, 385, 226 });
	countdown.frames.PushBack({ 859, 43, 385, 226 });
	countdown.frames.PushBack({ 450, 44, 385, 226 });
	countdown.frames.PushBack({ 41, 44, 385, 226 });
	
	countdown.speed = 0.02f;
	

}

bool ModuleMap::Start()
{
	LOG("Loading Intro scene");


	scroll = { 0, 0, 320, 240 };
	music_on = true;
	map = true;

	map_selection = App->textures->Load("ryu_mapa.png");
	versus_image = App->textures->Load("countdownVS.png");

	music_versus = App->audio->LoadFx("musica_versus.wav");

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
	
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP || map == false)
	{
		map = false;

		if (music_on){

			App->audio->PlayFx(music_versus);
			music_on = false;

		}
		

		scroll = countdown.GetCurrentFrame();

		App->renderer->Blit(versus_image, 40, 7, &scroll);

		if ((App->input->GetKey(SDL_SCANCODE_RSHIFT) == KEY_UP) || (countdown.getFrame() >= (countdown.frames.Count() - countdown.speed)))
		{
			
			//App->fade->FadeToBlack(App->map, App->scene_ken, FADE_TIME);
		}
		
	}

	if(map == true){
		App->renderer->Blit(map_selection, 70, 0, &scroll);
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