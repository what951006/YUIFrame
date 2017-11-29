#include "stdafx.h"
#include "YPoint.h"
#include "YUIObject.h"
#include "YWin32Application.h"

YPoint YPoint::MapFromMain(YUIObject* des)
{
	YPoint pos(0,0);
	while (des)
	{
		if(!des->IsWindow())
			pos+= des->GetPos();
		des = dynamic_cast<YUIObject*>(des->GetParent());
	}
	return pos;
}
YPoint YPoint::MapFromGlobal(YUIObject* des)
{
	YPoint&&pos=MapFromMain(des);
	des=YWin32Application::GetUIObjectByHWND(des->GetHwnd());
	YPoint&&pos2 = des->GetPos();
	pos+=pos2;
	return pos;
}

YPoint& YPoint::operator+= (const YPoint &pos)
{
	this->x+=pos.x;
	this->y+=pos.y;
	return *this;
}

YPoint& YPoint::operator -= (const YPoint &pos)
{
	this->x-=pos.x;
	this->y-=pos.y;
	return *this;
}