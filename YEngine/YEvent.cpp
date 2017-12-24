#include "stdafx.h"
#include "YEvent.h"

#include "YObject.h"
#include "YWin32Application.h"
#include "YRect.h"
#include "YPoint.h"
#include "YTimer.h"

YEvent::YEvent(YObject*pParent)
	:YObject(pParent)
{

}


YEvent::~YEvent(void)
{

}

void YEvent::SendEvent(YObject*obj,YUIObject*pMain,EventType evtype,int x,int y,int width,int height)
{
	EventObject eobj;
	eobj.sender=obj;
	eobj.type=evtype;
	eobj.x=x;
	eobj.y=y;
	eobj.width=width;
	eobj.height=height;

	pMain->OnEventOccoured(eobj);
}

void YEvent::Update()
{
	YObject::Update();
}

YUIObject* YEvent::GetJudgeChild(HWND hwnd,const YPoint pos)
{
	for(auto hl : YWin32Application::GetHwndList())
		if(hl.hwnd == hwnd)
			return FindUIObjHelper(hl.pObj->GetGeometryFromMain(),hl.pObj,pos);
	return nullptr;
}

YUIObject* YEvent::GetJudgeChild(int nTimerID)
{
	for(auto item : YTimer::s_TimerVec)
		if(item.timerID == nTimerID)
			return item.pObj;

	return nullptr;
}

YUIObject* YEvent::FindUIObjHelper(YRect re,YUIObject* pObj,const YPoint point)
{
	if(!pObj)
		return nullptr;
	re=pObj->GetGeometryFromMain();
	if(re.IsContained(point) && pObj->IsShow())
	{
		YUIObject* pResult=nullptr;
		for (auto child : pObj->GetChildren())
		{
			pResult=FindUIObjHelper(re,dynamic_cast<YUIObject*>(child),point);
			if(pResult)
				return pResult;
		}
		if(!pResult)
			return pObj;
	}
	return nullptr;
}