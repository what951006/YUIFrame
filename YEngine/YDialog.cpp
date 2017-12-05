#include "stdafx.h"
#include "YDialog.h"
#include "YWin32Application.h"


LRESULT CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	int wmId, wmEvent;
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		break;
	case WM_CREATE:
		{
		}
		break;
	case WM_LBUTTONDOWN:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			YUIObject*pResult= YWin32Application::GetEvent()->GetJudgeChild(hWnd,YPoint(xPos,yPos));
			YUIObject*pMain=YWin32Application::GetUIObjectByHWND(hWnd);
			YWin32Application::GetEvent()->SendEvent(pResult,pMain,MOUSE_PRESS_DOWN_L,xPos,yPos);

			SetTimer(hWnd,YWIN_TIMER_ID,10,NULL);
			s_prePress=pResult;
		}
		break;
	case WM_LBUTTONUP:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			YUIObject*pResult= YWin32Application::GetEvent()->GetJudgeChild(hWnd,YPoint(xPos,yPos));
			YUIObject*pMain=YWin32Application::GetUIObjectByHWND(hWnd);
			YWin32Application::GetEvent()->SendEvent(pResult,pMain,MOUSE_PRESS_UP_L,xPos,yPos);
		}
		break;
	case WM_TIMER:
		{
			if(YWIN_TIMER_ID == wParam)
			{
				if(s_prePress)
				{
					if(0 == GetAsyncKeyState(1))//1为左键，2为右键
					{
						s_prePress->SetPressedState(false);
						s_prePress=nullptr;
						KillTimer(hWnd,YWIN_TIMER_ID);
					}
				}
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			//main window leaves msg;
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof (tme);  
			tme.dwFlags = TME_LEAVE;  
			tme.dwHoverTime = HOVER_DEFAULT;  
			tme.hwndTrack = hWnd; 
			TrackMouseEvent(&tme);
			//////////////////////////
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			YUIObject*pNow= YWin32Application::GetEvent()->GetJudgeChild(hWnd,YPoint(xPos,yPos));
			YUIObject*pMain=YWin32Application::GetUIObjectByHWND(hWnd);

			if(!s_preMove)
			{//when mouse comes to windows,these codes will be called
				YWin32Application::GetEvent()->SendEvent(pNow,pMain,WINDOWS_ENTER,xPos,yPos);
				YWin32Application::GetEvent()->SendEvent(pNow,pMain,MOUSE_MOVE,xPos,yPos);
			}
			else
			{//comes from one to another
				if(s_preMove == pNow)//mouse moves frequently on the control
				{
					YWin32Application::GetEvent()->SendEvent(pNow,pMain,MOUSE_MOVE,xPos,yPos);
				}
				else//the first time
				{
					YWin32Application::GetEvent()->SendEvent(pNow,pMain,WINDOWS_ENTER,xPos,yPos);
					YWin32Application::GetEvent()->SendEvent(s_preMove,pMain,WINDOWS_LEAVE,xPos,yPos);
				}
			}
			s_preMove = pNow;
		}
		break;
	case WM_MOUSELEAVE:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			YUIObject*pMain=YWin32Application::GetUIObjectByHWND(hWnd);
			if(s_preMove && s_preMove!=pMain)//极端情况，控件在边缘，追加一个离开情况
				YWin32Application::GetEvent()->SendEvent(s_preMove,pMain,WINDOWS_LEAVE,xPos,yPos);
			YWin32Application::GetEvent()->SendEvent(pMain,pMain,WINDOWS_LEAVE,xPos,yPos);
			s_preMove=nullptr;
		}
		break;
	case WM_RBUTTONDOWN:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			YUIObject*pResult= YWin32Application::GetEvent()->GetJudgeChild(hWnd,YPoint(xPos,yPos));
			YUIObject*pMain=YWin32Application::GetUIObjectByHWND(hWnd);

			YWin32Application::GetEvent()->SendEvent(pResult,pMain,MOUSE_PRESS_DOWN_R,xPos,yPos);
		}
		break;
	case WM_RBUTTONUP:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			YUIObject*pResult= YWin32Application::GetEvent()->GetJudgeChild(hWnd,YPoint(xPos,yPos));
			YUIObject*pMain=YWin32Application::GetUIObjectByHWND(hWnd);
			YWin32Application::GetEvent()->SendEvent(pResult,pMain,MOUSE_PRESS_UP_R,xPos,yPos);
		}
		break;
	case WM_SIZE:
		{
			int width  = LOWORD(lParam);
			int height = HIWORD(lParam);

			RECT re;
			GetWindowRect(hWnd,&re);
			YUIObject*pResult=YWin32Application::GetUIObjectByHWND(hWnd);
			YWin32Application::GetEvent()->SendEvent(pResult,pResult,WINDOWS_SIZE_CHANGED,re.left,re.top,width,height);
		}
		break;
	case WM_MOVE:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam);

			YUIObject*pMain=YWin32Application::GetUIObjectByHWND(hWnd);
			YWin32Application::GetEvent()->SendEvent(pMain,pMain,WINDOWS_MOVE_CHANGED,xPos,yPos);
		}
		break;
	case WM_ERASEBKGND:
		return 1;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			YRect &&re= YWin32Application::GetUIObjectByHWND(hWnd)->GetGeometry();

			HDC hdc=BeginPaint(hWnd,&ps);
			HDC memDc= CreateCompatibleDC(hdc);
			HBITMAP bitmap= CreateCompatibleBitmap(hdc,re.width,re.height);
			SelectObject(memDc,bitmap);

			YWin32Application::GetUIObjectByHWND(hWnd)->DrawWindow(memDc);

			BitBlt(hdc,0,0,re.width,re.height,memDc,0,0,SRCCOPY);
			DeleteDC(memDc);
			DeleteObject(bitmap);
			EndPaint(hWnd,&ps);
		}
		break;
	case WM_DESTROY:
		PostMessage(hWnd,WM_QUIT,0,0);
		YWin32Application::RemoveOneHwnd(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

YDialog::YDialog(HWND hwnd)
	:YUIObject(nullptr,false)
	,m_Parhwnd(hwnd)
{
	m_pParent=nullptr;
	YRegisterClass();
	InitInstance(GetYClassName(),_T("YModal"));
	YUIObject * pUI=YWin32Application::GetUIObjectByHWND(hwnd);
	SetGeometry(pUI->GetGeometry());

	YWin32Application::AddHwnd(GetHwnd(),this);
}

YDialog::~YDialog(void)
{
	
}


void YDialog::YRegisterClass()
{
	HBRUSH BGBru=CreateSolidBrush(RGB(180,180,180));
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= DialogProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= YWin32Application::GetInstance();
	wcex.hIcon			= LoadIcon(YWin32Application::GetInstance(), MAKEINTRESOURCE(IDI_YENGINE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= BGBru;
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= GetYClassName();
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassEx(&wcex);
}


void YDialog::InitInstance(LPCWSTR classname,LPCWSTR title)
{
	m_hWnd= CreateWindow(
			classname,
			title,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			m_Parhwnd,
			NULL,
			(HINSTANCE)GetWindowLong(m_Parhwnd, GWL_HINSTANCE),
			NULL);
}

int YDialog::Modal()
{
	EnableWindow(m_Parhwnd,FALSE);
	Show();
	MSG msg;
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	EnableWindow(m_Parhwnd,TRUE);
	SetForegroundWindow(m_Parhwnd);
	return 1;
}


