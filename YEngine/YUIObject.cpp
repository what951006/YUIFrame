#include "stdafx.h"
#include "YUIObject.h"
#include "YWin32Application.h"
#include <gdiplusbrush.h>





YUIObject::YUIObject(YObject*pParent)
	:YObject(pParent)
{
	if(!pParent)
	{
		//create a window here
		m_bWindow=true;
		YRegisterClass();
		InitInstance();
		DrawWindow();
	}
	else
	{
		YUIObject *parent=dynamic_cast<YUIObject*>(pParent);
		m_hRootWnd=parent->m_hRootWnd;
		m_bWindow=false;
	}
}


YUIObject::~YUIObject(void)
{
	
}

void YUIObject::YRegisterClass()
{
	m_BGBru=CreateSolidBrush(RGB(180,180,180));
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= YWin32Application::GetInstance();
	wcex.hIcon			= LoadIcon(YWin32Application::GetInstance(), MAKEINTRESOURCE(IDI_YENGINE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= m_BGBru;
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= GetAppClassName();
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassEx(&wcex);
}

bool YUIObject::InitInstance()
{
   m_hRootWnd= CreateWindow(GetAppClassName(), _T("Win32Appliction"), WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, YWin32Application::GetInstance(), NULL);
   if (!m_hRootWnd)
   {
      return FALSE;
   }
  
   YWin32Application::AddHwnd(m_hRootWnd,this);
   return TRUE;
}


void YUIObject::SetGeometry(int x,int y,int w,int h,bool bMove)
{
	m_re.x=x;
	m_re.y=y;
	m_re.width=w;
	m_re.height=h;

	if(bMove)
	{
		if(m_bWindow)
		{
			MoveWindow(m_hRootWnd,x,y,w,h,false);
			Update();
		}
	}
	DrawWindow();
	Update();
}
void YUIObject::DrawWindow()
{
	//if it is window
	if(m_bWindow)
	{

	}
	else
	{
		
	}

	for(YObject*obj : GetChildren())//¸¸×ª×ÓÀà
	{
		YUIObject* pChild=dynamic_cast<YUIObject*>(obj);
		if(pChild)
			pChild->DrawWindow();
	}
}

void YUIObject::Show(bool bShow)
{
	DrawWindow();
	bShow? ShowWindow(m_hRootWnd,SW_SHOW): ShowWindow(m_hRootWnd,SW_HIDE);
	UpdateWindow(m_hRootWnd);
}
bool YUIObject::OnEventOccoured(EventObject obj)
{
	/*~*/
	bool bResult=false;
	
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
			YPoint pos=YPoint::MapFromMain(this);
			for(auto child : GetChildren())
			{
				if(child->OnEventOccoured(obj))
					return true;
			}
		}
		break;
	case MOUSE_PRESS_UP_L:
		{
			
		}	
		break;
	case MOUSE_MOVE:
		{
			
		}
		break;
	case WINDOWS_SIZE:
		{
			SetGeometry(obj.x,obj.y,obj.width,obj.height,false);
		}
		break;
	default:
		break;
	}
	return YObject::OnEventOccoured(obj);
}

YRect YUIObject::GetGeometryFromMain()
{
	YRect re=GetGeometry();
	re.x= YPoint::MapFromMain(this).x;
	re.y=YPoint::MapFromMain(this).y;
	return re;
}