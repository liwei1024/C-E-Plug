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

BYTE getSCan(INT key)
{
	BYTE sCan = MapVirtualKey(key, 0);
	if (
		key == VK_LEFT ||
		key == VK_RIGHT ||
		key == VK_DOWN ||
		key == VK_UP
		)
	{
		sCan += 0x80;
	}
	return sCan;
}

VOID keyDown(INT key)
{
	if (isKeyPressed(key) == FALSE)
		keybd_event(key, getSCan(key), KEYEVENTF_EXTENDEDKEY | 0, 0);
}

VOID keyUp(INT key)
{
	if (isKeyPressed(key) == TRUE)
		keybd_event(key, getSCan(key), KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

VOID doKeyPress(INT key, INT s)
{
	keyDown(key);
	Sleep(s + createRandom(100, 150));
	keyUp(key);
	Sleep(100);
}
