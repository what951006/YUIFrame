#ifndef GENERAL_DEF_H
#define GENERAL_DEF_H


enum EventType:short
{
	YEVENT_ALL,//Don't use this item!
	//below events were handled by us with logic
	MOUSE_CLICKED_L,
	MOUSE_CLICKED_R,

	WINDOWS_ENTER,
	WINDOWS_LEAVE,

	//below events were handled by win system,we just dispatch them
	MOUSE_PRESS_DOWN_L,
	MOUSE_PRESS_UP_L,

	MOUSE_PRESS_DOWN_R,
	MOUSE_PRESS_UP_R,

	MOUSE_MOVE,

	WINDOWS_SIZE_CHANGED,
	WINDOWS_MOVE_CHANGED
};



#define YWIN_TIMER_ID 0

#define YCLASS_NAME "YUIFrame"
#define YDLG_CLA_NAME "YDlgFrame"

#endif