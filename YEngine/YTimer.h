#ifndef   YTIMER_H
#define  YTIMER_H

/**************************************************
@brief:the timer class 
@file:YTimer.h
@version:1.0
@company:null
@author:yantao
@email:what951006@163.com
@time:2017-12-24 18:40:55
**************************************************/
#include "YObject.h"
#include "YUIObject.h"

struct T_MAP{
	unsigned int timerID;
	YUIObject* pObj;
};

class YTimer : public YObject
{
public:
	YTimer(YUIObject*pParent);
	
	~YTimer(void);

	void Start(int uElapse);

	void Stop();

	unsigned int  GetTimerID(){return m_nTimerID;}

	static void AddTimerList(YUIObject*pParent);

	static void RemoveTimerList(unsigned int nID);

	static vector<T_MAP> s_TimerVec;

	static unsigned int s_nID;

	int m_state;

	enum {
		YTIMER_STOPPED,
		YTIMER_RUNNING
	};

	unsigned int m_nTimerID;
	
};

#endif //YTIMER_H


