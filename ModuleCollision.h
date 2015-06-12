#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#include "Module.h"
#include "p2List.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_NEUTRAL_1,
	COLLIDER_NEUTRAL_2,
	COLLIDER_DEFENSE_1,
	COLLIDER_DEFENSE_2,
	COLLIDER_PUNCH_1,
	COLLIDER_PUNCH_2,
	COLLIDER_KICK_1,
	COLLIDER_KICK_2,
	COLLIDER_HADOUKEN_1,
	COLLIDER_HADOUKEN_2,
	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete;
	COLLIDER_TYPE type;
	Module* callback;


	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = NULL) :
		rect(rectangle),
		type(type),
		callback(callback),
		to_delete(false)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(SDL_Rect r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision(Application* app, bool start_enabled = true);
	~ModuleCollision();

	bool check_collision = false;
	update_status PreUpdate();
	update_status Update();

	bool CleanUp();

	void Init_rec(SDL_Rect &rect, int x_pos, int y_pos, int width, int height){
		
		rect.h = height;
		rect.w = width;
		rect.x = x_pos;
		rect.y = y_pos;

	}

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = NULL);
	void DrawDebug(Collider* col);

private:

	p2List<Collider*>	colliders;
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug;
};

#endif // __ModuleCollision_H__