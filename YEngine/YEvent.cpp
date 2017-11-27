#include "stdafx.h"
#include "YEvent.h"

#include "YObject.h"
#include "YWin32Application.h"
#include "YRect.h"
#include "YPoint.h"


YEvent::YEvent(YObject*pParent)
	:YObject(pParent)
{

}


YEvent::~YEvent(void)
{

}

void YEvent::SendEvent(YObject*obj,YObject*pMain,EventType evtype,int x,int y)
{
	EventObject eobj;
	eobj.sender=obj;
	eobj.pMainWin=pMain;
	eobj.type=evtype;
	eobj.x=x;
	eobj.y=y;
	m_que.push(eobj);	
}

void YEvent::Update()
{
	while (!m_que.empty())
	{
		EventObject &eventobj=m_que.front();
		eventobj.sender->OnEventOccoured(eventobj);
		m_que.pop();
	}
	YObject::Update();
}

YObject* YEvent::GetJudgeChild(HWND hwnd,const YPoint pos)
{
	for(auto hl : YWin32Application::GetHwndList())
	{
		if(hl.hwnd == hwnd)
		{
			YRect re;
			re.width=hl.pObj->GetGeometry().width;
			re.height=hl.pObj->GetGeometry().height;
			return FindObjHelper(re,hl.pObj,pos);
		}
	}
	return nullptr;
}

YObject* YEvent::FindObjHelper(YRect re,YObject* obj,const YPoint point)
{
	if(!obj)
		return nullptr;

	YObject* pResult=nullptr;
	for (auto child : obj->GetChildren())
	{
		YUIObject*pobj= dynamic_cast<YUIObject*>(child);

		re.width=pobj->GetGeometry().width;
		re.height=pobj->GetGeometry().height;
		re.x += pobj->GetGeometry().x;
		re.y += pobj->GetGeometry().y;

		pResult=FindObjHelper(re,child,point);
		if(re.IsContained(point))
			return !pResult ? pobj:nullptr;
	}

	return pResult;
}