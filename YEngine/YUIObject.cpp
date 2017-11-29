#include "stdafx.h"
#include "YUIObject.h"
#include "YWin32Application.h"
#include <gdiplusbrush.h>
#include "YPainter.h"




YUIObject::YUIObject(YObject*pParent,bool bCreate)
	:YObject(pParent)
{
	if(!pParent && bCreate)
	{
		CreateWin(_T(YCLASS_NAME),L"YUI");
		m_bWindow=true;
	}
	else
	{
		YUIObject *parent=dynamic_cast<YUIObject*>(pParent);
		if(parent)
		{
			m_hRootWnd=parent->m_hRootWnd;
			m_bWindow=false;
		}
	}
}


YUIObject::~YUIObject(void)
{
	YWin32Application::RemoveOneHwnd(GetHwnd());
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
   m_hRootWnd= CreateWindow(classname, title, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, YWin32Application::GetInstance(), NULL);
   if (!m_hRootWnd)
   {
      return FALSE;
   }
   return TRUE;
}


void YUIObject::SetGeometry(int x,int y,int w,int h,bool bMove)
{
	m_re.x=x;
	m_re.y=y;
	m_re.width=w;
	m_re.height=h;

	if(bMove && m_bWindow)
		MoveWindow(m_hRootWnd,x,y,w,h,false);
}
void YUIObject::DrawWindow(HDC &dc)
{
	//if it is window
	YPainter painter(dc,this);
	if(m_bWindow)
	{

	}
	else
	{
		
	}

	for(YObject*obj : GetChildren())//base to derived
	{
		YUIObject* pChild=dynamic_cast<YUIObject*>(obj);
		if(pChild)
			pChild->DrawWindow(dc);
	}
}

void YUIObject::Show(bool bShow)
{

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
			if(obj.sender == this)
			{
				YPoint pos(obj.x,obj.y);
				pos-=YPoint::MapFromMain(this);

				OnMouseMove(pos);
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
	YRect &&re=GetGeometry();
	YPoint &&pt=YPoint::MapFromMain(this);
	re.x= pt.x;
	re.y=pt.y;
	return re;
}