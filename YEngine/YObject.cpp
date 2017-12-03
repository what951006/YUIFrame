#include "stdafx.h"
#include "YObject.h"
#include "YUIObject.h"
#include "YEvent.h"


int YObject::s_preTimerID=1;
YObject::YObject(YObject*pParent)
{
	m_pParent=pParent;
	if(pParent)
		pParent->GetChildren().push_back(this);
}


YObject::~YObject(void)
{
	//First y need delete children ,then delete from parent list
	if(m_pParent)
	{
		vector<YObject*> &vec=m_pParent->GetChildren();
		vector<YObject*>::iterator it=vec.begin();
		for(;it!= vec.end();it++)
		{
			if(this == *it)
			{
				vec.erase(it);
				break;
			}
		}
	}
}

void YObject::Update()
{
	for(YObject* pTemp : m_ChildVec)
		pTemp->Update();
}

bool YObject::OnEventOccoured(EventObject obj)
{
	/*
		how to translate message?
	*/
	return false;
}