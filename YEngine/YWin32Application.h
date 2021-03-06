#pragma once
/**************************************************
@brief: the win32 application instance
@file: YWin32Application.h
@version:v1.0
@company:casino.ltd
@author:yantao
@email:what951006@163.com
@time:2017-11-20 13:22:15
**************************************************/

#include "YObject.h"
#include "YUIObject.h"
#include "YEvent.h"

extern YUIObject *s_preMove;
extern YUIObject *s_prePress;


struct HPMAP	//hwnd and pointer,they map to each other
{
	HWND hwnd;
	YUIObject *pObj;
};

class YWin32Application :public YObject
{

public:
	YWin32Application(HINSTANCE instance);

	~YWin32Application(void);


	/*
	@brief:message loop here!!
	@param:NULL
	@return:Exit value
	*/
	int Run();


	/*
	@brief:virtual Update 
	@param:
	@return:
	*/
	virtual void Update();


	static HINSTANCE GetInstance(){return s_instance;}

	static void AddHwnd(HWND hwnd,YUIObject*obj){HPMAP hp={hwnd,obj}; s_hvec.push_back(hp);}

	static vector<HPMAP>&  GetHwndList(){return s_hvec;}

	static void RemoveOneHwnd(HWND hwnd);

	static void QuitApp(){PostQuitMessage(0);}

	static YEvent* GetEvent(){return &s_pApp->m_Event;}

	static YUIObject* GetUIObjectByHWND(HWND hwnd);
private:

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
	bool InitInstance();




	static YWin32Application* s_pApp;
	static HINSTANCE s_instance;
	static vector<HPMAP> s_hvec;
	static bool s_exit;
	YEvent m_Event;


	//gdi
	GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_gdiplusToken;
};

