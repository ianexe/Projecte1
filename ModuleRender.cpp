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

// PreUpdate: clear buffer a
update_status ModuleRender::PreUpdate()
{
	SDL_RenderClear(renderer);
	return UPDATE_CONTINUE;
}

// Update: debug camera
update_status ModuleRender::Update()
{
	float speed = 9;
	char title[250];

	//sprintf_s(title, "Camera X: %f Player1X: %f Player2X: %f", -(camera.x), (App->player->position.x), (App->player2->position.x));
	sprintf_s(title, "Player1 Health: %i Player2 Health: %i", (App->player->Health), (App->player2->Health));

	App->window->SetTitle(title);

	distance = App->player->position.x + App->player2->position.x;

	//SDL_Rect CameraBorders

	

		camera.x = (-(distance / 2 - 192) * 3);
	if (camera.x <= -1513){
	
		camera.x = -1513;
	}
	
	//CAMBIAR-HO
	/*if(App->input->GetKey(SDL_SCANCODE_UP) == 1)
		App->renderer->camera.x += speed;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == 1){
	
		App->renderer->camera.x -= speed;
	}*/


		if (App->renderer->camera.x >= 0)
		{
			App->renderer->camera.x = 0;
		}

		OpCamera.x = (-camera.x / 3);
	
	
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
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed, bool mirror)
{
	bool ret = true;
	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x * SCREEN_SIZE;
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


	if (mirror)
	{
		if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
		{
			LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			ret = false;
		}
	}
		
	else
	{
		if (SDL_RenderCopyEx(renderer, texture, section, &rect, 0, 0, SDL_FLIP_HORIZONTAL) != 0)
		{
			LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			ret = false;
		}
	}
	

	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if (use_camera)
	{
		rec.x = (int)(camera.x + rect.x * SCREEN_SIZE);
		rec.y = (int)(camera.y + rect.y * SCREEN_SIZE);
		rec.w *= SCREEN_SIZE;
		rec.h *= SCREEN_SIZE;
	}

	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}


