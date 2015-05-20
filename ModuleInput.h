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
	//Input Queue
	

	//State Machine Methods
	bool external_input2(p2Qeue<p2_inputs>& inputs2);
	bool external_input1(p2Qeue<p1_inputs>& inputs);
	
	
	//Getters
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