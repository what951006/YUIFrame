#include "stdafx.h"
#include "YWin32Application.h"

HINSTANCE YWin32Application::s_instance=NULL;
vector<HPMAP> YWin32Application::s_hvec;
bool YWin32Application::s_exit=false;
YWin32Application* YWin32Application::s_pApp=nullptr;
mutex g_mutex;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		break;
	case WM_CREATE:
		break;
	case WM_LBUTTONDOWN:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			YUIObject*pResult= YWin32Application::GetEvent()->GetJudgeChild(hWnd,YPoint(xPos,yPos));
			YUIObject*pMain=YWin32Application::GetUIObjectByHWND(hWnd);
			if(pResult)
			   YWin32Application::GetEvent()->SendEvent(pResult,pMain,MOUSE_PRESS_DOWN_L,xPos,yPos);
		}
		break;
	case WM_LBUTTONUP:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			YUIObject*pResult= YWin32Application::GetEvent()->GetJudgeChild(hWnd,YPoint(xPos,yPos));
			YUIObject*pMain=YWin32Application::GetUIObjectByHWND(hWnd);
			if(pResult)
			{
				YWin32Application::GetEvent()->SendEvent(pResult,pMain,MOUSE_PRESS_UP_L,xPos,yPos);
			}
		}
		break;
	case WM_RBUTTONDOWN:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			YUIObject*pResult= YWin32Application::GetEvent()->GetJudgeChild(hWnd,YPoint(xPos,yPos));
			YUIObject*pMain=YWin32Application::GetUIObjectByHWND(hWnd);
			if(pResult)
				YWin32Application::GetEvent()->SendEvent(pResult,pMain,MOUSE_PRESS_DOWN_R,xPos,yPos);
		}
		break;
	case WM_RBUTTONUP:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			YUIObject*pResult= YWin32Application::GetEvent()->GetJudgeChild(hWnd,YPoint(xPos,yPos));
			YUIObject*pMain=YWin32Application::GetUIObjectByHWND(hWnd);
			if(pResult)
				YWin32Application::GetEvent()->SendEvent(pResult,pMain,MOUSE_PRESS_UP_R,xPos,yPos);
		}
		break;
	case WM_MOUSEMOVE:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			YUIObject*pResult= YWin32Application::GetEvent()->GetJudgeChild(hWnd,YPoint(xPos,yPos));
			YUIObject*pMain=YWin32Application::GetUIObjectByHWND(hWnd);
			if(pResult)
				YWin32Application::GetEvent()->SendEvent(pResult,pMain,MOUSE_MOVE,xPos,yPos);
		}
		break;
	case WM_SIZE:
		{
			int width  = LOWORD(lParam);
			int height = HIWORD(lParam);

			RECT re;
			GetWindowRect(hWnd,&re);
			YUIObject*pResult=YWin32Application::GetUIObjectByHWND(hWnd);	
			if(pResult)
				YWin32Application::GetEvent()->SendEvent(pResult,pResult,WINDOWS_SIZE,re.left,re.top,width,height);
		}
		break;
	case WM_ERASEBKGND:
		return 1;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc=BeginPaint(hWnd,&ps);
			HDC memDc= CreateCompatibleDC(hdc);
			YRect &&re= YWin32Application::GetUIObjectByHWND(hWnd)->GetGeometry();
			HBITMAP bitmap= CreateCompatibleBitmap(hdc,re.width,re.height);
			SelectObject(memDc,bitmap);
			
			YWin32Application::GetUIObjectByHWND(hWnd)->DrawWindow(memDc);

			BitBlt(hdc,0,0,re.width,re.height,memDc,0,0,SRCCOPY);
			ReleaseDC(hWnd,memDc);

			EndPaint(hWnd,&ps);
		}
		break;
	case WM_DESTROY:
		if(YWin32Application::GetHwndList()[0].hwnd == hWnd)
		{
			YWin32Application::QuitApp();
			PostMessage(hWnd,WM_QUIT,0,0);
		}
		YWin32Application::RemoveOneHwnd(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}




YWin32Application::YWin32Application(HINSTANCE instance)
	:m_Event(this)
{
	s_instance=instance;
	s_pApp=this;
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);
}



YWin32Application::~YWin32Application(void)
{
	GdiplusShutdown(m_gdiplusToken);
}

int YWin32Application::Run()
{
	MSG msg;
	while (!s_exit)
	{
		while(GetMessage (&msg,NULL, 0, 0)) 
		{
			TranslateMessage (&msg); 
			DispatchMessage (&msg); 
		}

	}
	return 1;
}



void YWin32Application::Update()
{
	YObject::Update();
	/*Here is your code !!*/
	for(auto hp : s_hvec)
		hp.pObj->Update();
}


void YWin32Application::RemoveOneHwnd(HWND hwnd)
{
	lock_guard<mutex> lg(g_mutex);
	vector<HPMAP>::iterator it=s_hvec.begin();
	for(;it != s_hvec.end();it++)
	{
		if(hwnd == (*it).hwnd)
		{
			s_hvec.erase(it);
			break;
		}
	}
}
YUIObject* YWin32Application::GetUIObjectByHWND(HWND hwnd)
{
	lock_guard<mutex> lg(g_mutex);
	for(auto hp  :  s_hvec)
		if(hp.hwnd==hwnd)
			return hp.pObj;

	return nullptr;
}