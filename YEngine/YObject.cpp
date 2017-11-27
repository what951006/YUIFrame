#include "stdafx.h"
#include "YObject.h"
#include "YUIObject.h"
#include "YEvent.h"

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
		vector<YObject*>::iterator it;
		for(it=vec.begin();it!= vec.end();it++)
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
	switch(obj.type)
	{
	case MOUSE_PRESS_DOWN_L:
		{
			YUIObject* uiobj=dynamic_cast<YUIObject*>(this);
			YPoint pos=YPoint::MapFromMain(uiobj);
			if(uiobj)
			{
				for(auto child : GetChildren())
				{
					uiobj=dynamic_cast<YUIObject*>(this);
					if(uiobj)
					{
						if(uiobj->OnEventOccoured(obj))
						{
							uiobj->OnMouseDown(pos);
							return true;
						}
					}
				}
				YPoint pos(obj.x,obj.y);
				if(uiobj->GetGeometryFromMain().IsContained(pos))
				{
					uiobj->OnMouseDown(pos);
					return true;
				}
				else
					return false;
			}	
		}
		break;
	case MOUSE_PRESS_UP_L:
		{
			YUIObject* uiobj=dynamic_cast<YUIObject*>(this);
			if(uiobj)
				uiobj->OnMouseUp(YPoint(obj.x,obj.y));
		}
		break;
	default:
		break;
	}

	

	return false;
}