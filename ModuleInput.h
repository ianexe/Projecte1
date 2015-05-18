#pragma once
#include "Module.h"
#include "Globals.h"
#include "States.h"
#include "p2Qeue.h"


enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:

	ModuleInput(Application* app, bool start_enabled = true);
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

	//State Machine Methods
	bool external_input(p2Qeue<p1_inputs>& inputs);
	void internal_input(p2Qeue<p1_inputs>& inputs);
	p1_states process_fsm(p2Qeue<p1_inputs>& inputs);

	//Timers
	Uint32 jump_timer;
	Uint32 punch_timer;
	Uint32 hit_timer;


	KEY_STATE GetKey(int id) const
	{
		return keyboard[id];
	}

	int GetMouseX() const
	{
		return mouse_x;
	}

	int GetMouseY() const
	{
		return mouse_y;
	}

private:
	KEY_STATE* keyboard;
	int mouse_x;
	int mouse_y;
};