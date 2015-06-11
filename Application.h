#pragma once

#include "List.h"
#include "Globals.h"
#include "Module.h"
#include "Dummy.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneKen.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneHonda.h"
#include "ModuleIntro.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "ModuleMap.h"
#include "ModuleParticles.h"


class Application
{
public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleSceneKen* scene_ken;
	ModulePlayer* player;
	ModulePlayer2* player2;
	ModuleFadeToBlack* fade;
	ModuleSceneHonda* scene_honda;
	ModuleCollision* colision;
	ModuleIntro* scene_intro;
	ModuleUI* ui;
	ModuleParticles* particles;
	ModuleMap * map;
private:

	p2List<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	void AddModule(Module* mod);
};