#ifndef GENERAL_DEF_H
#define GENERAL_DEF_H
#include "YObject.h"
#include "YPoint.h"
#include "YRect.h"

enum EventType
{
	MOUSE_PRESS_DOWN_L,
	MOUSE_PRESS_UP_L,

	MOUSE_PRESS_DOWN_R,
	MOUSE_PRESS_UP_R,

	MOUSE_MOVE,

	WINDOWS_SIZE_CHANGED,
	WINDOWS_MOVE_CHANGED
};


struct EventObject
{
	YObject *sender;
	EventType type;
	int x;
	int y;
	int width;
	int height;
};

#define YCLASS_NAME "YUIFrame"
#define YDLG_CLA_NAME "YDlgFrame"

#endif