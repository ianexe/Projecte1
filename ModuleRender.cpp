#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include <assert.h>
#include <stdio.h>
ModuleRender::ModuleRender(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	renderer = NULL;
	camera.x = 0;
	camera.y = 0;
	//camera.w = SCREEN_WIDTH;
	//camera.h = SCREEN_HEIGHT;
	
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if(VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	
	if(renderer == NULL)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRender::PreUpdate()
{
	SDL_RenderClear(renderer);
	centerCameraX = -camera.x - 192;
	distance = App->player->position.x - App->player2->position.x;
	return UPDATE_CONTINUE;
}

// Update: debug camera
update_status ModuleRender::Update()
{
	int speed = 6;
	char title[250];
	sprintf_s(title, "Camera X: %i Player1X: %i", -(camera.x), (App->player->position.x));
	App->window->SetTitle(title);
	//SDL_Rect CameraBorders


	//camera.x = -(distance / 2) - 192;

	if(App->input->keyboard[SDL_SCANCODE_UP] == 1)
		App->renderer->camera.y += speed;




		if (App->input->keyboard[SDL_SCANCODE_DOWN] == 1)
			App->renderer->camera.y -= speed;





		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == 1 || App->input->keyboard[SDL_SCANCODE_D] == 1)
		{
			
				App->renderer->camera.x -= speed;
			
		}

		if (App->input->keyboard[SDL_SCANCODE_LEFT] == 1 || App->input->keyboard[SDL_SCANCODE_A] == 1)
		{
			
				App->renderer->camera.x += speed;
				
		}

		if (App->renderer->camera.x >= 0)
		{
			App->renderer->camera.x = 0;
		}

		//TODO POSAR UN SCENE LEN I ACABAR LA CAMERA
				//if (App->renderer->camera.x > App->scene_honda)
	/*	if (distance > 10)
		{
			App->renderer->camera.x = 0.0;
		}*/

	/*	if (App->renderer->centerCameraX < distance || -App->renderer->camera.x < distance2)
		{
			App->renderer->camera.x -= speed;
		}

		if (App->renderer->camera.x > distance / 2)
		{
			App->renderer->camera.x += speed;
		}
		*/
		/*if (App->input->keyboard[SDL_SCANCODE_LEFT] == 1 )
		{
			
			
			//assert(App->renderer->camera.x > -(App->player->position.x));
			App->renderer->camera.x += speed;

		}

	
		if (App->renderer->camera.x >= -1400)
		{
			//if ((App->player->position.x) + 500 < App->renderer->displacement.x - SCREEN_WIDTH){
			//if (-(App->player->position.x) < App->renderer->camera.x + 100){
			App->renderer->camera.x -= speed;
			//}
		}
	//}*/
	
	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRender::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if(renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed)
{
	bool ret = true;
	SDL_Rect rect;
	rect.x = (int) (camera.x * speed) + x * SCREEN_SIZE;
	rect.y = (int) (camera.y * speed) + y * SCREEN_SIZE;


	if(section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if(SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}


//Set Rect

void ModuleRender::setScreenBorders()
{/*
	displacement.x = App->renderer->camera.x; // SCREEN_SIZE);
	displacement.w = SCREEN_WIDTH;
	displacement.h = SCREEN_HEIGHT;
	//displacement.y = (int)(camera.y * speed) * SCREEN_SIZE;
	*/
}
