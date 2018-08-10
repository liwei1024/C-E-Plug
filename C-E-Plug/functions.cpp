#include "stdafx.h"
#include "functions.h"
#include "lua_import.h"
#include <ctime>
#include <tlhelp32.h>


INT createRandom(INT min, INT max)
{
	INT random = 0;
	if (max > min) {
		srand((unsigned)time(NULL));
		random = (rand() % (min - max + 1) + max);
	}
	else {
		srand((unsigned)time(NULL));
		random = (rand() % (max - min + 1) + min);
	}
	return random;
}

BOOL isKeyPressed(INT key)
{
	if (GetKeyState(key) < 0) {
		return TRUE;
	}
	return FALSE;
}

VOID keyDown(INT key)
{
	if (isKeyPressed(key) == FALSE)
		keybd_event(key, MapVirtualKey(key, 0), 0, 0);
}

VOID keyUp(INT key)
{
	if (isKeyPressed(key) == TRUE)
		keybd_event(key, MapVirtualKey(key, 0), KEYEVENTF_KEYUP, 0);
}

VOID doKeyPress(INT key, INT s)
{
	keyDown(key);
	Sleep(s + createRandom(50, 100));
	keyUp(key);
	Sleep(100);
}