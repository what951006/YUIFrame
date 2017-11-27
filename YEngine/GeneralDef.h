#ifndef GENERAL_DEF_H
#define GENERAL_DEF_H
#include "YObject.h"

enum EventType
{
	MOUSE_PRESS_DOWN_L,
	MOUSE_PRESS_UP_L,

	MOUSE_PRESS_DOWN_R,
	MOUSE_PRESS_UP_R
};


struct EventObject
{
	YObject *sender;
	YObject *pMainWin;
	EventType type;
	int x;
	int y;
};

#endif