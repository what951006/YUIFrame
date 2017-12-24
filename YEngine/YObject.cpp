#include "stdafx.h"
#include "YObject.h"
#include "YUIObject.h"
#include "YEvent.h"
#include "GeneralDef.h"



YObject::YObject(YObject*pParent)
{
	m_pParent=pParent;
	if(pParent)
		pParent->GetChildren().push_back(this);
}


YObject::~YObject(void)
{
	//First y need delete children ,then delete from parent list
	for (auto pObj:m_msg_vec)
		pObj->RemoveEventObserver(YEVENT_ALL,this);
	if(m_pParent)
	{
		vector<YObject*> &vec=m_pParent->GetChildren();
		auto it=vec.begin();
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

bool YObject::OnEventOccoured(EventObject &obj)
{
	/*
		how to translate message?
	*/
	return false;
}

void YObject::AddEventObserver(EventType evt,YObject*pObj)
{
	pObj->m_msg_vec.push_back(this);

	auto &vec = m_msg_map[evt];
	auto it=find(vec.begin(),vec.end(),pObj);
	if (it==vec.end())
		vec.push_back(pObj);
}

void YObject::RemoveEventObserver(EventType evt,YObject*pobj)
{
	if(YEVENT_ALL == evt)
	{
		//all the things
		for(auto it=m_msg_map.begin();it!=m_msg_map.end();it++)
		{
			auto &vec=it->second;
			for(auto it2=vec.begin();it2!=vec.end();it2++)
			{
				if(*it2 == pobj)
				{
					vec.erase(it2);
					break;
				}
			}

		}
		return ;
	}
	auto &vec = m_msg_map[evt];
	auto it=find(vec.begin(),vec.end(),pobj);
	if (it==vec.end())
		vec.push_back(*it);
	else
		vec.erase(it);

}

void YObject::NofityAllObserver(EventType evtype)
{
	auto &vec = m_msg_map[evtype];
	for(auto it = vec.begin();it != vec.end();it++)  
	{
		EventObject eo;
		eo.type=evtype;
		eo.sender=this;
		(*it)->OnEventOccoured(eo);
	}
}