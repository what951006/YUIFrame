#pragma once
/**************************************************
@brief:The base class of almost all classes
@file:Yobject.h
@version:v1.0
@company:casino.ltd
@author:yantao
@email:what951006@163.com
@time:2017-11-20 12:54:24
**************************************************/

struct EventObject;
class YEvent;

class YObject
{
public:
	YObject(YObject*pParent=nullptr);
	virtual ~YObject(void);


	/*
	@brief:update
	@param:
	@return:
	*/
	virtual void Update();

	/*
	@brief:Get Children object
	@param:
	@return:vector of children
	*/
	vector<YObject*>& GetChildren(){return m_ChildVec;}


	/*
	@brief:Add child to children list
	@param:child pointer
	@return:
	*/
	void AddChild(YObject *pChild);


	/*
	@brief:
	@param:
	@return:parent pointer
	*/
	YObject* GetParent(){return m_pParent;}

	/*
	@brief:
	@param:
	@return:
	*/
	virtual bool OnEventOccoured(EventObject obj);


	void StartTimer(int interival){}

	void EndTimer(){}

	virtual void OnTimerEvent(){}
protected:

	vector<YObject*> m_ChildVec;

	vector<int> m_TimerID;
	YObject *m_pParent;
	int m_timer;
	static 	int s_preTimerID;
};