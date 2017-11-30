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
		SetWindowPos(m_hRootWnd,NULL,x,y,w,h,false);
}


void YUIObject::SetGeometry(const YRect &re,bool bMove)
{
	m_re=re;
	if(bMove && m_bWindow)
		SetWindowPos(m_hRootWnd,NULL,re.x,re.y,re.width,re.height,false);
}

void YUIObject::DrawWindow(HDC &dc)
{
	//if it is window
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

		/*Image *img= Image::FromFile(L"D:\\test.png");
		painter.DrawImage(*img,0,0,m_re.width,m_re.height);
		delete img;*/
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
			if(obj.sender == this)
			{
				YPoint pos(obj.x,obj.y);
				pos-=YPoint::MapFromMain(this);
				
				OnMouseUp(pos);
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
	case WINDOWS_SIZE_CHANGED:
		{
			m_re.x=obj.x;
			m_re.y=obj.y;
			m_re.width=obj.width;
			m_re.height=obj.height;
		}
		break;
	case WINDOWS_MOVE_CHANGED:
		{
			m_re.x=obj.x;
			m_re.y=obj.y;
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
	re.y= pt.y;
	return re;
}