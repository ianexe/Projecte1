enum game_states
{
	IDLE,
	WALK_RIGHT,
	PUNCH
};

state = game_states;
switch (state){
case IDLE:
	//Animation?
	if (/*KEY_RIGHT == 1 KEYREPEAT*/)
	{
		state = WALK_RIGHT;
	}
	break;

case WALK_RIGHT:
	if (/*KEY_RIGHT == 1*/)
	{
		state = WALK_RIGHT;
	}
	else
	{
		state =IDLE;
	}

	if (/*KEY_Z == 1 KEYREPEAT*/)
	{
		state = PUNCH;
	}
	break;
case PUNCH:
	if (punch_done == true)
	{
		state = IDLE;
	}
	
}