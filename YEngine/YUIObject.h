#pragma once
/**************************************************
@brief: the UI object of all UI windows
@file: YUIObject.h
@version:v1.0
@company:casino.ltd
@author:yantao
@email:what951006@163.com
@time:2017-11-20 13:01:40
**************************************************/
#include "YObject.h"
#include "YRect.h"
#include "YPoint.h"

class YUIObject :public YObject
{
	//friend class YObject;
public:
	YUIObject(YObject *pParent=nullptr,bool bCreate=true);

	~YUIObject(void);

	void CreateWin(LPCWSTR classname,LPCWSTR title);

	void SetGeometry(int x,int y,int w,int h,bool bMove=true);

	void SetGeometry(const YRect &re,bool bMove=true);

	/*
	@brief:Register class name
	@param:
	@return:
	*/
	void YRegisterClass();
	
	/*
	@brief:initialize instance
	@param:
	@return:true successful ,false failed
	*/
	bool InitInstance(LPCWSTR classname,LPCWSTR title);
	

	/*
	@brief:show or hide window and widget
	@param:bool 
	@return:
	*/
	void Show(bool bShow=true);


	/*
	@brief:Get the Name of YClass 
	@param:
	@return:
	*/
	LPCWSTR GetYClassName(){return _T(YCLASS_NAME);}
	

	/*
	@brief:Get geometry,in another way ,Get this Rect 
	@param:
	@return:YRect
	*/
	YRect GetGeometry(){return m_re;}


	/*
	@brief:get Rect from main window ,not global window!
	@param:
	@return:the Rect in main window
	*/
	YRect GetGeometryFromMain();

	YPoint GetPosFromMain();


	YPoint GetPos(){return YPoint(m_re.x,m_re.y);}

	HWND GetHwnd(){return m_hWnd;}

	bool IsWindow(){return m_bWindow;}

	void SetWindowTitle(const string &str){ SetWindowTextA(GetHwnd(),str.c_str());}

	virtual void DrawWindow(HDC dc);

	virtual void Update() override;

	virtual bool OnEventOccoured(EventObject &obj) override;

	virtual void OnMouseDown(const YPoint &point);

	virtual void OnMouseMove(const YPoint &point);

	virtual void OnMouseUp(const YPoint &point);

	virtual void OnMouseEnter(const YPoint &point);

	virtual void OnMouseLeave(const YPoint &point);

	virtual void OnMouseLClicked(YUIObject*);

	virtual void OnMouseRClicked(YUIObject*);
	
	virtual void OnTimerEvent(unsigned int nTimerID);


	void SetEnterState(bool bEnter=true){m_bEnter=bEnter; Update();}

	void SetPressedState(bool bPress=true){m_bPress=bPress;Update();}

	bool IsShow(){return m_bShow;}

	int GetWidth(){return m_re.width;}

	int GetHeight(){return m_re.height;}

	int GetX(){return GetParent() ? m_re.x : 0;}
	
	int GetY(){return GetParent() ? m_re.y : 0;}

	void SetFixedSize(bool bFixed=true){m_bFixedsize=bFixed;}

	bool IsFixedSize(){return m_bFixedsize;}

	YRect GetMinSize(){return YRect(0,0,m_nMinW,m_nMinH);}

	YRect GetMaxSize(){return YRect(0,0,m_nMaxW,m_nMaxH);}
protected:
	YRect m_re;

	int m_nMinW;
	int m_nMinH;
	int m_nMaxW;
	int m_nMaxH;

	HBRUSH m_BGBru;
	HWND m_hWnd;

	bool m_bFixedsize;
	bool m_bWindow;
	
	bool m_bEnter;
	bool m_bPress;
	bool m_bShow;

	
};

