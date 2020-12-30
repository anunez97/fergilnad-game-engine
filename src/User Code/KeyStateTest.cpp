// Key State Test

#include "KeyStateTest.h"

KeyStateTest::KeyStateTest(AZUL_KEY k)
	:key(k), currstate(false), prevstate(false)
{
}

void KeyStateTest::TestKey()
{
	currstate = Keyboard::GetKeyState(key);

	if (currstate == true && currstate != prevstate)
	{
		DebugMsg::out("Key pressed\n");
	}
	else if(currstate == false && currstate != prevstate)
	{
		DebugMsg::out("Key released\n");
	}

	prevstate = currstate;
}