#pragma once
#include "YObject.h"
/**************************************************
@brief:event class!
@file:YEvent.h
@version:v1.0
@company:casino.ltd
@author:yantao
@email:what951006@163.com
@time:2017-11-20 15:32:28
**************************************************/
class YPoint;
struct YRect;



class YEvent :public YObject
{
public:
	YEvent(YObject*pParent);

	~YEvent(void);

	void SendEvent(YObject*obj,YUIObject*pMain,EventType evtype,int x=0,int y=0,int width=0,int height=0);

	void Update();

	YUIObject* GetJudgeChild(HWND hwnd,const YPoint pos);

	
private:

	YUIObject* FindUIObjHelper(YRect re,YUIObject*,const YPoint);

	queue<EventObject> m_que;
};















