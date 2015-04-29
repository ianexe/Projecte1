#include "Globals.h"
#include "Application.h"
#include "ModuleCollision.h"

ModuleCollision::ModuleCollision(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = false;

	matrix[COLLIDER_PLAYER1_BODY][COLLIDER_PLAYER1_BODY] = false;
	matrix[COLLIDER_PLAYER1_BODY][COLLIDER_PLAYER2_BODY] = false;
	matrix[COLLIDER_PLAYER1_BODY][COLLIDER_PLAYER1_PUNCH] = false;
	matrix[COLLIDER_PLAYER1_BODY][COLLIDER_PLAYER2_PUNCH] = true;
	matrix[COLLIDER_PLAYER1_BODY][COLLIDER_PLAYER1_PUNCH2] = false;
	matrix[COLLIDER_PLAYER1_BODY][COLLIDER_PLAYER2_PUNCH2] = true;
	matrix[COLLIDER_PLAYER1_BODY][COLLIDER_PLAYER1_KICK] = false;
	matrix[COLLIDER_PLAYER1_BODY][COLLIDER_PLAYER2_KICK] = true;

	matrix[COLLIDER_PLAYER2_BODY][COLLIDER_PLAYER1_BODY] = false;
	matrix[COLLIDER_PLAYER2_BODY][COLLIDER_PLAYER2_BODY] = false;
	matrix[COLLIDER_PLAYER2_BODY][COLLIDER_PLAYER1_PUNCH] = true;
	matrix[COLLIDER_PLAYER2_BODY][COLLIDER_PLAYER2_PUNCH] = false;
	matrix[COLLIDER_PLAYER2_BODY][COLLIDER_PLAYER1_PUNCH2] = true;
	matrix[COLLIDER_PLAYER2_BODY][COLLIDER_PLAYER2_PUNCH2] = false;
	matrix[COLLIDER_PLAYER2_BODY][COLLIDER_PLAYER1_KICK] = true;
	matrix[COLLIDER_PLAYER2_BODY][COLLIDER_PLAYER2_KICK] = false;

	matrix[COLLIDER_PLAYER1_PUNCH][COLLIDER_PLAYER1_BODY] = false;
	matrix[COLLIDER_PLAYER1_PUNCH][COLLIDER_PLAYER2_BODY] = true;
	matrix[COLLIDER_PLAYER1_PUNCH][COLLIDER_PLAYER1_PUNCH] = false;
	matrix[COLLIDER_PLAYER1_PUNCH][COLLIDER_PLAYER2_PUNCH] = false;
	matrix[COLLIDER_PLAYER1_PUNCH][COLLIDER_PLAYER1_PUNCH2] = false;
	matrix[COLLIDER_PLAYER1_PUNCH][COLLIDER_PLAYER2_PUNCH2] = false;
	matrix[COLLIDER_PLAYER1_PUNCH][COLLIDER_PLAYER1_KICK] = false;
	matrix[COLLIDER_PLAYER1_PUNCH][COLLIDER_PLAYER2_KICK] = false;

	matrix[COLLIDER_PLAYER2_PUNCH][COLLIDER_PLAYER1_BODY] = true;
	matrix[COLLIDER_PLAYER2_PUNCH][COLLIDER_PLAYER2_BODY] = false;
	matrix[COLLIDER_PLAYER2_PUNCH][COLLIDER_PLAYER1_PUNCH] = false;
	matrix[COLLIDER_PLAYER2_PUNCH][COLLIDER_PLAYER2_PUNCH] = false;
	matrix[COLLIDER_PLAYER2_PUNCH][COLLIDER_PLAYER1_PUNCH2] = false;
	matrix[COLLIDER_PLAYER2_PUNCH][COLLIDER_PLAYER2_PUNCH2] = false;
	matrix[COLLIDER_PLAYER2_PUNCH][COLLIDER_PLAYER1_KICK] = false;
	matrix[COLLIDER_PLAYER2_PUNCH][COLLIDER_PLAYER2_KICK] = false;

	matrix[COLLIDER_PLAYER1_PUNCH2][COLLIDER_PLAYER1_BODY] = false;
	matrix[COLLIDER_PLAYER1_PUNCH2][COLLIDER_PLAYER2_BODY] = true;
	matrix[COLLIDER_PLAYER1_PUNCH2][COLLIDER_PLAYER1_PUNCH] = false;
	matrix[COLLIDER_PLAYER1_PUNCH2][COLLIDER_PLAYER2_PUNCH] = false;
	matrix[COLLIDER_PLAYER1_PUNCH2][COLLIDER_PLAYER1_PUNCH2] = false;
	matrix[COLLIDER_PLAYER1_PUNCH2][COLLIDER_PLAYER2_PUNCH2] = false;
	matrix[COLLIDER_PLAYER1_PUNCH2][COLLIDER_PLAYER1_KICK] = false;
	matrix[COLLIDER_PLAYER1_PUNCH2][COLLIDER_PLAYER2_KICK] = false;

	matrix[COLLIDER_PLAYER2_PUNCH2][COLLIDER_PLAYER1_BODY] = true;
	matrix[COLLIDER_PLAYER2_PUNCH2][COLLIDER_PLAYER2_BODY] = false;
	matrix[COLLIDER_PLAYER2_PUNCH2][COLLIDER_PLAYER1_PUNCH] = false;
	matrix[COLLIDER_PLAYER2_PUNCH2][COLLIDER_PLAYER2_PUNCH] = false;
	matrix[COLLIDER_PLAYER2_PUNCH2][COLLIDER_PLAYER1_PUNCH2] = false;
	matrix[COLLIDER_PLAYER2_PUNCH2][COLLIDER_PLAYER2_PUNCH2] = false;
	matrix[COLLIDER_PLAYER2_PUNCH2][COLLIDER_PLAYER1_KICK] = false;
	matrix[COLLIDER_PLAYER2_PUNCH2][COLLIDER_PLAYER2_KICK] = false;

	matrix[COLLIDER_PLAYER1_KICK][COLLIDER_PLAYER1_BODY] = false;
	matrix[COLLIDER_PLAYER1_KICK][COLLIDER_PLAYER2_BODY] = true;
	matrix[COLLIDER_PLAYER1_KICK][COLLIDER_PLAYER1_PUNCH] = false;
	matrix[COLLIDER_PLAYER1_KICK][COLLIDER_PLAYER2_PUNCH] = false;
	matrix[COLLIDER_PLAYER1_KICK][COLLIDER_PLAYER1_PUNCH2] = false;
	matrix[COLLIDER_PLAYER1_KICK][COLLIDER_PLAYER2_PUNCH2] = false;
	matrix[COLLIDER_PLAYER1_KICK][COLLIDER_PLAYER1_KICK] = false;
	matrix[COLLIDER_PLAYER1_KICK][COLLIDER_PLAYER2_KICK] = false;

	matrix[COLLIDER_PLAYER2_KICK][COLLIDER_PLAYER1_BODY] = true;
	matrix[COLLIDER_PLAYER2_KICK][COLLIDER_PLAYER2_BODY] = false;
	matrix[COLLIDER_PLAYER2_KICK][COLLIDER_PLAYER1_PUNCH] = false;
	matrix[COLLIDER_PLAYER2_KICK][COLLIDER_PLAYER2_PUNCH] = false;
	matrix[COLLIDER_PLAYER2_KICK][COLLIDER_PLAYER1_PUNCH2] = false;
	matrix[COLLIDER_PLAYER2_KICK][COLLIDER_PLAYER2_PUNCH2] = false;
	matrix[COLLIDER_PLAYER2_KICK][COLLIDER_PLAYER1_KICK] = false;
	matrix[COLLIDER_PLAYER2_KICK][COLLIDER_PLAYER2_KICK] = false;
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	p2List_item<Collider*>* tmp = colliders.getFirst();
	p2List_item<Collider*>* tmp2;

	while (tmp != NULL)
	{
		tmp2 = tmp->next;
		if (tmp->data->to_delete == true)
		{
			delete tmp->data;
			colliders.del(tmp);
		}
		tmp = tmp2;
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{
	LOG("Loading collision scene");
	p2List_item<Collider*>* tmp = colliders.getFirst();

	Collider* c1;
	Collider* c2;

	while (tmp != NULL)
	{
		c1 = tmp->data;

		// Debug ---
		if (debug)
			DrawDebug(c1);

		p2List_item<Collider*>* tmp2 = tmp->next; // avoid checking collisions already checked
		while (tmp2 != NULL)
		{
			c2 = tmp2->data;

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}

			tmp2 = tmp2->next;
		}

		tmp = tmp->next;
	}



	// Debug ---
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	return UPDATE_CONTINUE;
}

void ModuleCollision::DrawDebug(Collider* col)
{
	LOG("Hola me he activado");
	Uint8 alpha = 80;
	switch (col->type)
	{
	case COLLIDER_NONE:
		App->renderer->DrawQuad(col->rect, 255, 255, 255, alpha);
		break;
	case COLLIDER_PLAYER1_BODY:
		App->renderer->DrawQuad(col->rect, 0, 0, 255, alpha);
		break;
	case COLLIDER_PLAYER2_BODY:
		App->renderer->DrawQuad(col->rect, 0, 255, 0, alpha);
		break;
	case COLLIDER_PLAYER1_PUNCH:
		App->renderer->DrawQuad(col->rect, 255, 0, 0, alpha);
		break;
	case COLLIDER_PLAYER2_PUNCH:
		App->renderer->DrawQuad(col->rect, 255, 255, 0, alpha);
		break;
	case COLLIDER_PLAYER1_PUNCH2:
		App->renderer->DrawQuad(col->rect, 255, 0, 0, alpha);
		break;
	case COLLIDER_PLAYER2_PUNCH2:
		App->renderer->DrawQuad(col->rect, 255, 255, 0, alpha);
		break;
	case COLLIDER_PLAYER1_KICK:
		App->renderer->DrawQuad(col->rect, 0, 255, 255, alpha);
		break;
	case COLLIDER_PLAYER2_KICK:
		App->renderer->DrawQuad(col->rect, 0, 255, 255, alpha);
		break;
	}

}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	p2List_item<Collider*>* item = colliders.getLast();

	while (item != NULL)
	{
		delete item->data;
		item = item->prev;
	}

	colliders.clear();
	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = new Collider(rect, type, callback);
	colliders.add(ret);
	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(SDL_Rect r) const
{
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}