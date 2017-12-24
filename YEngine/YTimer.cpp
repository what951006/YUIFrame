#include "stdafx.h"
#include "YTimer.h"





vector<T_MAP> YTimer::s_TimerVec;
unsigned int YTimer::s_nID=2;

YTimer::YTimer(YUIObject*pParent)
	:YObject(pParent)
	,m_state(YTIMER_STOPPED)
{
	s_nID++;
	m_nTimerID = s_nID;

	AddTimerList(pParent);
}


YTimer::~YTimer(void)
{
	YUIObject*pParent=dynamic_cast<YUIObject*>(GetParent());
	if(pParent)
		KillTimer(pParent->GetHwnd(),m_nTimerID);
	
	RemoveTimerList(m_nTimerID);
}

void YTimer::Start(int uElapse)
{
	YUIObject*pParent=dynamic_cast<YUIObject*>(GetParent());
	if(YTIMER_STOPPED == m_state && pParent)
	{
		::SetTimer(pParent->GetHwnd(),m_nTimerID,uElapse,nullptr);
		m_state = YTIMER_RUNNING;
	}
}

void YTimer::Stop()
{
	YUIObject*pParent=dynamic_cast<YUIObject*>(GetParent());
	if(YTIMER_RUNNING == m_state && pParent)
	{
		::KillTimer(pParent->GetHwnd(),m_nTimerID);
		m_state = YTIMER_STOPPED;
	}
}

void YTimer::AddTimerList(YUIObject*pParent)
{
	T_MAP map;
	map.pObj = pParent;
	map.timerID = s_nID;
	s_TimerVec.push_back(map);
}

void YTimer::RemoveTimerList(unsigned int nID)
{
	
	for(auto it=s_TimerVec.begin(); it != s_TimerVec.end() ; it++)
	{
		if(nID == (*it).timerID)
		{
			s_TimerVec.erase(it);
			return;
		}
	}
}