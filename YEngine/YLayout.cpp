#include "stdafx.h"
#include "YLayout.h"
#include "YUIObject.h"

YLayout::YLayout(YUIObject*parent)
	:YObject(parent)
{
	GetParent()->AddEventObserver(YEVENT_WINDOWS_MOVE_CHANGED,this);
}


YLayout::~YLayout(void)
{

}
