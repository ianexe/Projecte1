#pragma once
#include "Application.h"

Application::Application()
{
	renderer = new ModuleRender(this);
	window = new ModuleWindow(this);
	textures = new ModuleTextures(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this);
	scene_ken = new ModuleSceneKen(this, false);
	player = new ModulePlayer(this, false);
	player2 = new ModulePlayer2(this, false);
	scene_honda = new ModuleSceneHonda(this, false);
	fade = new ModuleFadeToBlack(this);
	player_col = new ModuleCollision(this, false);
	player2_col = new ModuleCollision(this, false);
	scene_intro = new ModuleIntro(this, true);
	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(renderer);
	AddModule(textures);
	AddModule(input);
	AddModule(audio);

	// Scenes
	AddModule(scene_intro);
	AddModule(scene_ken);
	AddModule(scene_honda);
	
	// Characters
	AddModule(player);
	AddModule(player2);

	// Misc
	AddModule(fade); // let this after all drawing

	AddModule(player_col);
	AddModule(player2_col);
}

Application::~Application()
{
	delete renderer;
	delete window;
	delete textures;
	delete input;
	delete audio;
	delete scene_intro;
	delete scene_honda;
	delete scene_ken;
	delete player;
	delete player2;
	delete fade;
	delete player_col;
	delete player2_col;
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	p2List_item<Module*>* item = list_modules.getFirst();

	while(item != NULL && ret == true)
	{
		ret = item->data->Init();
		item = item->next;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = list_modules.getFirst();

	while(item != NULL && ret == true)
	{
		if(item->data->IsEnabled())
			ret = item->data->Start();
		item = item->next;
	}
	
	return ret;
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	p2List_item<Module*>* item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->PreUpdate();
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->Update();
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->PostUpdate();
		item = item->next;
	}

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	p2List_item<Module*>* item = list_modules.getLast();

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.add(mod);
}