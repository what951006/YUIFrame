#include "stdafx.h"
#include "YUIObject.h"
#include "YWin32Application.h"
#include "YPainter.h"
#include "YMessageBox.h"



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//wchar_t buf[64]={0};
	/*wsprintf(buf,L"message: %d \n",message);
	HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE) ;
	WriteConsole(hd ,buf ,wcslen(buf) , NULL , NULL );*/
	int wmId, wmEvent;
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		break;
	case WM_CREATE:
		{
			// default :create frameless windows

			//DWORD dwStyle = ::GetWindowLong(hWnd, GWL_STYLE)
			//	| WS_MAXIMIZEBOX | WS_MINIMIZEBOX
			//	| WS_SYSMENU | WS_SIZEBOX | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
			//dwStyle &= ~(WS_CAPTION|WS_THICKFRAME);

			//SetWindowLong(hWnd, GWL_STYLE, dwStyle); 
//透明度
//			SetWindowLong(hWnd,GWL_EXSTYLE,dwStyle);   
//			SetLayeredWindowAttributes(hWnd,0,0,LWA_ALPHA);  
//
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

			if(pResult!=s_prePress && s_prePress)
			{
				YWin32Application::GetEvent()->SendEvent(pResult,pMain,WINDOWS_ENTER,xPos,yPos);
			}
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
			if(s_prePress)
			{
				break;
			}

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
		if(YWin32Application::GetHwndList().size()==1)//the last one!!
		{
			YWin32Application::QuitApp();
			PostMessage(hWnd,WM_QUIT,0,0);
		}
		YWin32Application::RemoveOneHwnd(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}





YUIObject::YUIObject(YObject*pParent,bool bCreate)
	:YObject(pParent)
	,m_bEnter(false)
	,m_bPress(false)
	,m_bShow(true)
{
	if(!pParent && bCreate)
	{
		m_bWindow=true;
		CreateWin(_T(YCLASS_NAME),L"YUIFrame");
		
	}
	else
	{
		YUIObject *parent=dynamic_cast<YUIObject*>(pParent);
		if(parent)
		{
			m_bWindow=false;
			m_hWnd=parent->m_hWnd;
		}
	}
}


YUIObject::~YUIObject(void)
{


}

void YUIObject::CreateWin(LPCWSTR classname,LPCWSTR title)
{
	m_pParent=nullptr;
	m_bWindow=true;
	YRegisterClass();
	InitInstance(classname,title);
	YWin32Application::AddHwnd(GetHwnd(),this);
}

void YUIObject::YRegisterClass()
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= YWin32Application::GetInstance();
	wcex.hIcon			= LoadIcon(YWin32Application::GetInstance(), MAKEINTRESOURCE(IDI_YENGINE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= GetYClassName();
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassEx(&wcex);
}

bool YUIObject::InitInstance(LPCWSTR classname,LPCWSTR title)
{
   m_hWnd= CreateWindow(classname, title, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, YWin32Application::GetInstance(), NULL);
   if (!m_hWnd)
      return FALSE;
   return TRUE;
}


void YUIObject::SetGeometry(int x,int y,int w,int h,bool bMove)
{
	m_re.x=x;
	m_re.y=y;
	m_re.width=w;
	m_re.height=h;
	if(bMove && m_bWindow)
		SetWindowPos(m_hWnd,NULL,x,y,w,h,false);
}


void YUIObject::SetGeometry(const YRect &re,bool bMove)
{
	m_re=re;
	if(bMove && m_bWindow)
		SetWindowPos(m_hWnd,NULL,re.x,re.y,re.width,re.height,false);
}

void YUIObject::DrawWindow(HDC dc)
{	
	YPainter painter(dc,this);
	if(m_bWindow)
	{
		SolidBrush br(Color(255,240,240,240));
		Pen pen(Color(255,255,0,0));
		painter.SetPen(pen);
		painter.FillRect(br,0,0,m_re.width,m_re.height);

		painter.DrawLine(0,0,m_re.width,0);
		painter.DrawLine(m_re.width-1,1,m_re.width-1,m_re.height);
		painter.DrawLine(m_re.width-1,m_re.height-1,1,m_re.height-1);
		painter.DrawLine(0,m_re.height,0,0);
		painter.DrawLine(0,20,m_re.width,20);
	}
	else
	{
		//painter.SetTransparent(0);
	}
	HDC memDC=painter.GetMemDC();
	for(YObject*obj : GetChildren())//base to derived
	{
		YUIObject* pChild=dynamic_cast<YUIObject*>(obj);
		if(pChild && pChild->IsShow())
			pChild->DrawWindow(memDC);
	}
}

void YUIObject::Show(bool bShow)
{
	if(m_bWindow)
		bShow? ShowWindow(m_hWnd,SW_SHOW): ShowWindow(m_hWnd,SW_HIDE);

	m_bShow=bShow;
	Update();

}

void YUIObject::Update()
{
	//YObject::Update();
	InvalidateRect(m_hWnd,NULL,FALSE);
}

bool YUIObject::OnEventOccoured(EventObject &obj)
{
	/*~*/
	switch(obj.type)
	{
	case MOUSE_PRESS_DOWN_L:
		{
			if(obj.sender == this)
			{
				YPoint pos(obj.x,obj.y);
				pos-=YPoint::MapFromMain(this);
				
				OnMouseDown(pos);
				return true;
			}
			YPoint &&pos=YPoint::MapFromMain(this);
			for(auto child : GetChildren())
			{
				if(child->OnEventOccoured(obj))
					return true;
			}
		}
		break;
	case MOUSE_PRESS_UP_L:
		{
			if(obj.sender == this)
			{
				YPoint pos(obj.x,obj.y);
				pos-=YPoint::MapFromMain(this);
				
				OnMouseUp(pos);
				return true;
			}
			YPoint &&pos=YPoint::MapFromMain(this);
			for(auto child : GetChildren())
			{
				if(child->OnEventOccoured(obj))
					return true;
			}
		}	
		break;
	case MOUSE_MOVE:
		{
			if(obj.sender == this)
			{
				YPoint pos(obj.x,obj.y);
				pos-=YPoint::MapFromMain(this);

				OnMouseMove(pos);
				return true;
			}
			YPoint &&pos=YPoint::MapFromMain(this);
			for(auto child : GetChildren())
			{
				if(child->OnEventOccoured(obj))
					return true;
			}
		}
		break;
	case WINDOWS_SIZE_CHANGED:
		{
			m_re.x=obj.x;
			m_re.y=obj.y;
			m_re.width=obj.width;
			m_re.height=obj.height;

			NofityAllObserver(WINDOWS_SIZE_CHANGED);
		}
		break;
	case WINDOWS_MOVE_CHANGED:
		{
			m_re.x=obj.x;
			m_re.y=obj.y;
			NofityAllObserver(WINDOWS_MOVE_CHANGED);
		}
		break;
	case WINDOWS_ENTER:
		{
			if(obj.sender == this)
			{
				YPoint pos(obj.x,obj.y);
				pos-=YPoint::MapFromMain(this);

				OnMouseEnter(pos);
				return true;
			}
			YPoint &&pos=YPoint::MapFromMain(this);
			for(auto child : GetChildren())
			{
				if(child->OnEventOccoured(obj))
					return true;
			}
		}
		break;
	case WINDOWS_LEAVE:
		{
			if(obj.sender == this)
			{
				YPoint pos(obj.x,obj.y);
				pos-=YPoint::MapFromMain(this);
				OnMouseLeave(pos);
				return true;
			}
			YPoint &&pos=YPoint::MapFromMain(this);
			for(auto child : GetChildren())
			{
				if(child->OnEventOccoured(obj))
					return true;
			}
		}
		break;
	default:
		break;
	}
	return YObject::OnEventOccoured(obj);
}

void YUIObject::OnMouseDown(const YPoint &point)
{
	m_bPress=true;
	Update();
}

void YUIObject::OnMouseMove(const YPoint &point)
{
}

void YUIObject::OnMouseUp(const YPoint &point)
{
	if(m_bPress)
	{
		m_bPress=false;
		OnMouseLClicked(this);
		NofityAllObserver(MOUSE_CLICKED_L);
	}
}

void YUIObject::OnMouseEnter(const YPoint &point)
{
	m_bEnter=true;
	Update();
}

void YUIObject::OnMouseLeave(const YPoint &point)
{
	m_bEnter=false;
	Update();
}

void YUIObject::OnMouseLClicked(YUIObject*obj)
{
	
}

void YUIObject::OnMouseRClicked(YUIObject*)
{

}





YRect YUIObject::GetGeometryFromMain()
{
	if(YWin32Application::GetUIObjectByHWND(m_hWnd) == this)
		return YRect(0,0,m_re.width,m_re.height);

	YRect &&re=GetGeometry();
	YPoint &&pt=YPoint::MapFromMain(this);
	re.x= pt.x;
	re.y= pt.y;
	return re;
}