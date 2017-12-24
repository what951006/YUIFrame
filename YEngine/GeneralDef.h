#ifndef GENERAL_DEF_H
#define GENERAL_DEF_H


enum EventType:short
{
	YEVENT_ALL,//Don't use this item!
	//below events were handled by us with logic
	YEVENT_MOUSE_CLICKED_L,
	YEVENT_MOUSE_CLICKED_R,

	YEVENT_WINDOWS_ENTER,
	YEVENT_WINDOWS_LEAVE,

	//below events were handled by win system,we just dispatch them
	YEVENT_MOUSE_PRESS_DOWN_L,
	YEVENT_MOUSE_PRESS_UP_L,

	YEVENT_MOUSE_PRESS_DOWN_R,
	YEVENT_MOUSE_PRESS_UP_R,

	YEVENT_MOUSE_MOVE,

	YEVENT_WINDOWS_SIZE_CHANGED,
	YEVENT_WINDOWS_MOVE_CHANGED,
	YEVENT_TIMER
};



#define YWIN_TIMER_ID 0

#define YCLASS_NAME "YUIFrame"
#define YDLG_CLA_NAME "YDlgFrame"

#endif