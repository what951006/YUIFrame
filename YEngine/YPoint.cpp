#include "stdafx.h"
#include "YPoint.h"
#include "YUIObject.h"

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
YPoint& YPoint::operator+= (const YPoint &pos)
{
	this->x+=pos.x;
	this->y+=pos.y;
	return *this;
}